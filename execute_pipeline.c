/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:31:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/27 09:38:28 by kaisuzuk         ###   ########.fr       */
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

t_bool			do_piping(int pipe_in, int pipe_out);
void			close_pipe(t_pipefd *pipefd);
int				open_pipe(t_pipefd *pipefd, int *fildes);
int				execute_pipe_internal(t_pipefd *pipefd, int *fildes);

static pid_t	wait_for(pid_t lastpid)
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
	execve(command, arg, env);
	return (99); // ### TODO: エラー処理
}

static void	execute_disk_command(t_command *cmd, t_varlist *env)
{
	char	*command;
	char	**arg;
	char	**envarr;

	if (cmd->command->redirects && do_redirections(cmd->command->redirects,
			env) != 0)
	{
		exit(EXECUTION_FAILURE); // ### TODO: エラー処理
	}
	command = search_for_command(cmd->command->words->word->word, env);
	if (!command)
		exit(99); // ### TODO: エラー処理
	arg = strvec_from_word_list(cmd->command->words);
	if (!arg)
	{
		free(command);
		exit(99); // ### TODO: エラー処理
	}
	envarr = get_env_arr(env);
	if (!envarr)
		exit(99); // ### TODO: エラー処理
	exit(shell_execve(command, arg, envarr));
}

static int	execute_simple_command(t_pipefd pipefd, t_command *cmd,
		int close_fd, t_varlist *env)
{
	pid_t			pid;

	pid = fork();
	if (pid < 0)
		return (EXECUTION_FAILURE); // ### TODO: エラー処理
	if (pid == 0)
	{
		if (close_fd != -1)
			close(close_fd);
		if (!do_piping(pipefd.pipe_in, pipefd.pipe_out))
			return (EXECUTION_FAILURE); // ### TODO: エラー処理
		execute_disk_command(cmd, env);
	}
	return (pid);
}

static int	execute_pipeline(t_command *cmd, t_varlist *env)
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
				return (dispose_command(cmd), EXECUTION_FAILURE);
			// ### TODO: エラー処理
		}
		else
			fildes[0] = -1;
		lastpid = execute_simple_command(pipefd, cur_cmd, fildes[0], env);
		close_pipe(&pipefd);
		if (cur_cmd->next)
			pipefd.pipe_in = fildes[0];
		cur_cmd = cur_cmd->next;
	}
	return (wait_for(lastpid));
}

int	execute_cmd(t_command *cmd, t_varlist *env)
{
	// const char				*builtin_list[] = {"cd", "echo", "env", "export",
	// 					"pwd", "unset"};
	// const t_builtin_func	builtin_table[] = {builtin_cd, builtin_echo,
	// 		builtin_env, builtin_export, builtin_pwd, builtin_unset};
	const t_builtin builtin_table[] = {
		{"cd", builtin_cd}, 
		{"echo", builtin_echo},
		{"env", builtin_env},  
		{"export", builtin_export},
		{"pwd", builtin_pwd}, 
		{"unset", builtin_unset}, 
	}; 
	const size_t table_size = sizeof(builtin_table) / sizeof(builtin_table[0]);
	if (!cmd->next && is_builtin(cmd->command->words->word->word, builtin_table, table_size))
		return (execute_builtin_command(cmd->command, builtin_table, table_size, env));
	return (execute_pipeline(cmd, env));
}
