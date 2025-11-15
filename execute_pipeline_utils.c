/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:39:59 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 11:15:06 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// execute_pipeline.c
pid_t	wait_for(pid_t lastpid);

t_bool	open_pipe(t_pipefd *pipefd, int *fildes)
{
	if (pipe(fildes) < 0)
	{
		sys_error("pipe failed");
		if (pipefd->pipe_in != -1)
			close(pipefd->pipe_in);
		return (FALSE);
	}
	return (TRUE);
}

void	close_pipe(t_pipefd *pipefd)
{
	if (pipefd->pipe_in != -1)
		close(pipefd->pipe_in);
	if (pipefd->pipe_out != -1)
		close(pipefd->pipe_out);
}

t_bool	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != -1)
	{
		if (dup2(pipe_in, STDIN_FILENO) < 0)
			return (sys_error("dup2 failed"), FALSE);
		close(pipe_in);
	}
	if (pipe_out != -1)
	{
		if (dup2(pipe_out, STDOUT_FILENO) < 0)
			return (sys_error("dup2 failed"), FALSE);
		close(pipe_out);
	}
	return (TRUE);
}

t_bool	execute_pipe_internal(t_pipefd *pipefd, int *fildes)
{
	if (!open_pipe(pipefd, fildes))
	{
		if (pipefd->pipe_in != -1)
			close(pipefd->pipe_in);
		wait_for(-1); 
		return (FALSE);
	}
	pipefd->pipe_out = fildes[1];
	return (TRUE);
}

int	file_isdir(char *command)
{
	struct stat	sb;

	return ((!stat(command, &sb) && S_ISDIR(sb.st_mode)));
}