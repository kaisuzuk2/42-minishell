/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:31:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 13:39:52 by kaisuzuk         ###   ########.fr       */
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

pid_t	wait_for(pid_t lastpid)
{
	int		status;
	int		last_status;
	pid_t	wpid;

	last_status = -1;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
			break ;
		if (wpid == lastpid)
			last_status = status;
	}
	if (lastpid < 0)
		return (EXECUTION_FAILURE);
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
	return (i);
}

static int	execute_disk_command(t_command *cmd, const t_builtin *builtin_table,
		const size_t table_size, t_shell_env *shell_env)
{
	char	*command;
	char	**arg;
	char	**envarr;

	if (cmd->command->redirects && do_redirections(cmd->command->redirects,
			shell_env->env) != 0)
		return (EXECUTION_FAILURE);
	if (is_builtin(cmd->command->words->word->word, builtin_table, table_size))
		exit(execute_builtin_command(cmd, builtin_table, table_size, shell_env));
	command = search_for_command(cmd->command->words->word->word, shell_env->env);
	if (!command)
		return (fatal_error("malloc", MALLOC_ERR_STR), EXECUTION_FAILURE);
	if (!update_key_value(shell_env->env, "_", command))
		return (EXECUTION_FAILURE);
	arg = strvec_from_word_list(cmd->command->words);
	if (!arg)
		return (fatal_error("malloc", MALLOC_ERR_STR), EXECUTION_FAILURE);
	envarr = get_env_arr(shell_env->env);
	if (!envarr)
		return (fatal_error("malloc", MALLOC_ERR_STR), EXECUTION_FAILURE);
	exit(shell_execve(command, arg, envarr));
}

static int	execute_simple_command(t_pipefd pipefd, t_command *cmd,
		int close_fd, t_shell_env *shell_env)
{
	pid_t			pid;
	t_builtin_table builtin_info;

	builtin_info = get_builtin_table();
	if (pipefd.pipe_in == -1 && pipefd.pipe_out == -1
		&& is_builtin(cmd->command->words->word->word, builtin_info.table,
			builtin_info.size))
		return (execute_builtin_command(cmd, builtin_info.table, builtin_info.size, shell_env));
	pid = fork();
	if (pid < 0)
	{
		sys_error("fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		if (close_fd != -1)
			close(close_fd);
		if (!do_piping(pipefd.pipe_in, pipefd.pipe_out))
			exit(1);
		if (execute_disk_command(cmd, builtin_info.table, builtin_info.size,
				shell_env) == EXECUTION_FAILURE)
			exit(1);
	}
	return (pid);
}

int	execute_pipeline(t_command *cmd, t_shell_env *shell_env)
{
	int			fildes[2];
	t_pipefd	pipefd;
	pid_t		lastpid;
	t_command	*cur_cmd;

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
	return (wait_for(lastpid));
}
