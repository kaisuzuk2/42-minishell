/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:31:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/16 12:41:19 by kaisuzuk         ###   ########.fr       */
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

static int shell_execve(char *command, char **arg)
{
	execve(command, arg, environ);
}

static void execute_disk_command(t_command *cmd)
{
	char *command;
	char **arg;

	command = search_for_command(cmd->words->word->word);
	if (!command)
		exit(99); // ### TODO: エラー処理
	arg = strvec_from_word_list(cmd->words);
	if (!arg)
		free(command);
		exit(99); // ### TODO: エラー処理
	exit(shell_execve(command, arg));
}

static int execute_simple_command(t_command *cmd, t_pipefd pipefd, int close_fd)
{
	const pid_t pid = fork();

	if (pid < 0)
		return (EXECUTION_FAILURE); // ### TODO: エラー処理
	if (pid == 0)
	{
		if (close_fd != -1)
			close(close_fd);
		if (!do_piping(pipefd.pipe_in, pipefd.pipe_out))
			return (EXECUTION_FAILURE); // ### TODO: エラー処理
		else
			execute_disk_command(cmd);
	}
	return (pid);
}

int execute_pipeline(t_command *cmd)
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
	while (cur_cmd->next)
	{
		pipefd.pipe_out = -1;
		if (!execute_pipe_internal(&pipefd, fildes))
			return (EXECUTION_FAILURE); //### TODO: エラー処理
		lastpid = execute_simple_command(cur_cmd, pipefd, fildes[0]);
		cur_cmd = cur_cmd->next;
	}
	lastpid = execute_simple_command(cur_cmd, pipefd, fildes[0]);
	return (waitfor(lastpid));
}