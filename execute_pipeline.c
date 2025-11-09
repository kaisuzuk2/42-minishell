/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:31:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/08 13:01:24 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1) fork ()
2) connect pipes
3) look up the command
4) do redirections
5) execve ()
6) If the execve failed, see if the file has executable mode set.
   If so, and it isn't a directory, then execute its contents as
   a shell script.
*/

t_bool		do_piping(int pipe_in, int pipe_out);
void		close_pipe(t_pipefd *pipefd);
int			open_pipe(t_pipefd *pipefd, int *fildes);
int			execute_pipe_internal(t_pipefd *pipefd, int *fildes);

static void print_signal_end(int last_status)
{
	if (last_status == SIGINT)
		ft_dprintf(STDOUT_FILENO, "\n");
}

static void print_core_dumped(int last_status)
{
	if (last_status == SIGQUIT)
		ft_dprintf(STDOUT_FILENO, "Quit (core dumped)\n");
}

pid_t	wait_for(pid_t lastpid)
{
	int		status;
	int		last_status;
	pid_t	wpid;
	t_bool sig_flg;

	sig_flg = FALSE;
	last_status = -1;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
			break ;
		if (!sig_flg && WIFSIGNALED(status))
		{
			print_signal_end(WTERMSIG(status));
			sig_flg = TRUE;
		}
		if (wpid == lastpid)
			last_status = status;
	}
	if (lastpid < 0)
		return (EXECUTION_FAILURE);
	if (WIFSIGNALED(last_status))
		return (print_core_dumped(WTERMSIG(last_status)), 128 + WTERMSIG(last_status));
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else
		return (EXECUTION_FAILURE);
}

static int	shell_execve(char *command, char **arg, char **env)
{
	int		i;
	char	*re_args[3];

	execve(command, arg, env);
	i = errno;
	if (i != ENOEXEC)
	{
		if (i == ENOENT)
			fatal_error(command, NOTFOUND_STR);
	}
	else
		internal_error(command, strerror(i));
	// if (i == ENOEXEC)
	// {
	// 	re_args[0] = "/bin/bash";
	// 	re_args[1] = command;
	// 	re_args[2] = NULL;
	// 	execve(re_args[0], re_args, envp);
	// 	i = errno;
	// }
	return (EXECUTION_FAILURE);
}

static int	execute_disk_command(t_command *cmd, const t_builtin *builtin_table,
		const size_t table_size, t_shell_env *shell_env)
{
	char	*command;
	char	**arg;
	char	**envarr;

	if (cmd->command->redirects && do_redirections(cmd->command->redirects,
			shell_env) != 0)
		return (EXECUTION_FAILURE);
	if (is_builtin(cmd->command->words->word->word, builtin_table, table_size))
		return (execute_builtin_command(cmd, builtin_table, table_size, shell_env));
	command = search_for_command(cmd->command->words->word->word, shell_env->env);
	if (!command)
		return (fatal_error("malloc", MALLOC_ERR_STR), EX_FATAL_ERROR);
	if (!update_key_value(shell_env->env, "_", command))
		return (free(command), EX_FATAL_ERROR);
	arg = strvec_from_word_list(cmd->command->words);
	envarr = get_env_arr(shell_env->env);
	if (!envarr || !arg)
		return (free(command), dispose_char_arr(envarr), dispose_char_arr(arg), fatal_error("malloc", MALLOC_ERR_STR), EX_FATAL_ERROR);
	shell_execve(command, arg, envarr);
	return (free(command), dispose_char_arr(envarr), dispose_char_arr(arg), EXECUTION_FAILURE);
}

static pid_t	execute_simple_command(t_pipefd pipefd, t_command *cmd,
		int close_fd, t_shell_env *shell_env)
{
	pid_t			pid;
	t_builtin_table builtin_info;
	int status;

	builtin_info = get_builtin_table();
	if (pipefd.pipe_in == -1 && pipefd.pipe_out == -1
		&& is_builtin(cmd->command->words->word->word, builtin_info.table,
			builtin_info.size))
		return (execute_builtin_command(cmd, builtin_info.table, builtin_info.size, shell_env));
	pid = fork();
	if (pid < 0)
	{
		sys_error("fork failed");
		dispose_command(cmd->head);
		dispose_env(shell_env);
		exit(EXECUTION_FAILURE);
	}
	if (pid == 0)
	{
		reset_signals_for_child();
		if (close_fd != -1)
			close(close_fd);
		if (!do_piping(pipefd.pipe_in, pipefd.pipe_out))
		{
			dispose_command(cmd->head);
			dispose_env(shell_env);
			exit(EXECUTION_FAILURE);
		}
		status = execute_disk_command(cmd, builtin_info.table, builtin_info.size, shell_env);
		dispose_command(cmd->head);
		dispose_env(shell_env);
		exit(status);
	}
	return (pid);
}

int	execute_pipeline(t_command *cmd, t_shell_env *shell_env)
{
	int			fildes[2];
	t_pipefd	pipefd;
	pid_t		lastpid;
	t_command	*cur_cmd;
	int res;

	cur_cmd = cmd;
	pipefd.pipe_in = -1;
	while (cur_cmd)
	{
		pipefd.pipe_out = -1;
		if (cur_cmd->next)
		{
			if (!execute_pipe_internal(&pipefd, fildes))
				return (EXECUTION_FAILURE);
		}
		else
			fildes[0] = -1;
		lastpid = execute_simple_command(pipefd, cur_cmd, fildes[0], shell_env);
		close_pipe(&pipefd);
		if (cur_cmd->next)
			pipefd.pipe_in = fildes[0];
		cur_cmd = cur_cmd->next;
	}
	set_signal_for_parent();
	res = wait_for(lastpid);
	enter_prompt_mode();
	return (res);
}
