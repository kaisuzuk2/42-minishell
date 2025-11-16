/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:01:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 14:15:49 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			here_document_to_fd(t_redirect *r, t_shell_env *shell_env);

static int	redirect_to_fd(t_redirect *r)
{
	int	fd;
	int	to_fd;

	if (r->instruction == r_input_direction)
	{
		fd = open(r->redirectee.filename->word, O_RDONLY);
		to_fd = STDIN_FILENO;
	}
	else
	{
		fd = open(r->redirectee.filename->word, r->flags, 0666);
		to_fd = STDOUT_FILENO;
	}
	if (fd < 0)
		return (fatal_error(r->redirectee.filename->word, strerror(errno)),
			EXECUTION_ERR);
	if (dup2(fd, to_fd) < 0)
		return (sys_error("dup2 failed"), EXECUTION_ERR);
	close(fd);
	return (EXECUTION_SUCCESS);
}

static int	do_redirections_internal(t_redirect *redir, t_shell_env *shell_env)
{
	int	here_fd;

	if (redir->instruction == r_input_direction
		|| redir->instruction == r_output_direction
		|| redir->instruction == r_appending_to)
		return (redirect_to_fd(redir));
	else if (redir->next && redir->instruction == r_reading_until
		&& redir->next->instruction == r_reading_until)
		return (EXECUTION_SUCCESS);
	else
	{
		here_fd = here_document_to_fd(redir, shell_env);
		if (here_fd < 0)
			return (here_fd);
		if (dup2(here_fd, STDIN_FILENO) < 0)
			return (EXECUTION_ERR);
	}
	return (EXECUTION_SUCCESS);
}

int	do_redirections(t_command *cmd, t_shell_env *shell_env)
{
	t_redirect	*redir;
	int			status;

	redir = cmd->redirects;
	while (redir)
	{
		status = do_redirections_internal(redir, shell_env);
		if (status == EXECUTION_MEMERR)
		{
			dispose_command(cmd->head);
			dispose_env(shell_env);
			exit(EX_FATAL_ERROR);
		}
		if (status < 0)
			return (EXECUTION_FAILURE);
		redir = redir->next;
	}
	return (EXECUTION_SUCCESS);
}
