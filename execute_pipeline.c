/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:31:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/21 11:59:33 by kaisuzuk         ###   ########.fr       */
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
	char **envarr;

	if (cmd->command->redirects && do_redirections(cmd->command->redirects, env) != 0)
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

static int	execute_simple_command(t_command *cmd, t_pipefd pipefd,
		int close_fd, t_varlist *env)
{
	const pid_t	pid = fork();
	t_builtin_func *builtin;

	if (pid < 0)
		return (EXECUTION_FAILURE); // ### TODO: エラー処理
	if (pid == 0)
	{
		if (close_fd != -1)
			close(close_fd);
		if (!do_piping(pipefd.pipe_in, pipefd.pipe_out))
			return (EXECUTION_FAILURE); // ### TODO: エラー処理
		if (find_shell_builtin(cmd->command->words->word->word))
		{
			builtin = find_shell_builtin(cmd->command->words->word->word);
			builtin(cmd->command->words->next, env);
			exit(99);
		}
		else
			execute_disk_command(cmd, env);
	}
	return (pid);
}

int	execute_pipeline(t_varlist *env, t_command *cmd)
{
	int fildes[2];
	t_pipefd pipefd;
	pid_t lastpid;
	t_command *cur_cmd;

	cur_cmd = cmd;
	pipefd.pipe_in = -1;
	pipefd.pipe_out = -1;
	fildes[0] = -1;
	fildes[1] = -1;
	if (is_builtin(cur_cmd->command->words->word->word) && !cur_cmd->next)
		return (execute_builtin_command(cur_cmd->command, env));
	while (cur_cmd->next)
	{
		pipefd.pipe_out = -1;
		if (!execute_pipe_internal(&pipefd, fildes))
			return (EXECUTION_FAILURE); //### TODO: エラー処理
		lastpid = execute_simple_command(cur_cmd, pipefd, fildes[0], env);
		cur_cmd = cur_cmd->next;
	}
	lastpid = execute_simple_command(cur_cmd, pipefd, fildes[0], env);
	return (wait_for(lastpid));
}