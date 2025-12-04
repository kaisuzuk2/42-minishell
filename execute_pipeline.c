/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:31:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/12/05 02:17:34 by kaisuzuk         ###   ########.fr       */
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

// execute_pipeline_utils.c
t_bool			do_piping(int pipe_in, int pipe_out);
void			close_pipe(t_pipefd *pipefd);
t_bool			open_pipe(t_pipefd *pipefd, int *fildes);
t_bool			execute_pipe_internal(t_pipefd *pipefd, int *fildes);

// execute_cmd.c
int				execute_disk_command(t_command *cmd, t_shell_env *shell_env);

static int	execute_simple_command_internal(t_command *cmd, t_pipefd pipefd,
		int close_fd, t_shell_env *shell_env)
{
	int	status;

	reset_signals_for_child();
	if (close_fd != -1)
		close(close_fd);
	if (!do_piping(pipefd.pipe_in, pipefd.pipe_out))
	{
		dispose_command(cmd->head);
		dispose_env(shell_env);
		exit(EXECUTION_FAILURE);
	}
	status = execute_disk_command(cmd, shell_env);
	dispose_command(cmd->head);
	dispose_env(shell_env);
	exit(status);
}

static pid_t	execute_simple_command(t_pipefd pipefd, t_command *cmd,
		int close_fd, t_shell_env *shell_env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		sys_error("fork failed");
		dispose_command(cmd->head);
		dispose_env(shell_env);
		exit(EXECUTION_FAILURE);
	}
	if (pid == 0)
		exit(execute_simple_command_internal(cmd, pipefd, close_fd, shell_env));
	return (pid);
}

static t_bool	is_simple_command(t_command *cmd)
{
	return (!cmd->next && cmd->command && cmd->command->words);
}

static pid_t	execute_pipeline_internal(t_command *cmd, t_pipefd pipefd,
		t_shell_env *shell_env)
{
	pid_t	lastpid;
	int		fildes[2];

	while (cmd)
	{
		pipefd.pipe_out = -1;
		if (cmd->next && !execute_pipe_internal(&pipefd, fildes))
			return (-1);
		else if (!cmd->next)
			fildes[0] = -1;
		lastpid = execute_simple_command(pipefd, cmd, fildes[0], shell_env);
		close_pipe(&pipefd);
		if (cmd->next)
			pipefd.pipe_in = fildes[0];
		cmd = cmd->next;
	}
	return (lastpid);
}

int	execute_pipeline(t_command *cmd, t_shell_env *shell_env)
{
	t_pipefd	pipefd;
	pid_t		lastpid;
	t_command	*cur_cmd;
	int			res;

	cur_cmd = cmd;
	pipefd.pipe_in = -1;
	if (is_simple_command(cur_cmd)
		&& is_builtin(cur_cmd->command->words->word->word))
		return (pipefd.pipe_out = -1, execute_builtin_command(cmd, EX_SIMPLE,
				shell_env));
	lastpid = execute_pipeline_internal(cmd, pipefd, shell_env);
	set_signal_for_parent();
	res = wait_for(lastpid);
	enter_prompt_mode();
	return (res);
}
