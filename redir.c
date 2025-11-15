/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:01:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 17:48:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*heredoc_expand(t_redirect *r, size_t *lenp,
				t_shell_env *shell_env);

int	sh_mktmpfd(const char *nameroot, char **filename)
{
	*filename = ft_strjoin("/tmp/", nameroot);
	if (!*filename)
		return (internal_error("malloc", MALLOC_ERR_STR), -1);
	return (ft_mkstemp(filename));
}

static int	here_document_to_file(t_redirect *r)
{
	int		fd;
	int		fd2;
	char	*filename;

	fd = sh_mktmpfd("sh-thd", &filename);
	if (fd < 0)
		return (EXECUTION_FAILURE);
	ft_dprintf(fd, "%s", r->redirectee.filename->word);
	close(fd);
	fd2 = open(filename, O_RDONLY, 0600);
	if (fd2 < 0)
	{
		internal_error(filename, strerror(errno)); //### TODO: エラー処理
		unlink(filename);
		free(filename);
		return (EXIT_FAILURE);
	}
	if (unlink(filename) < 0)
	{
		close(fd2);
		free(filename);
		return (sys_error("unlink failed"), EXIT_FAILURE);
	}
	return (free(filename), fd2);
}

// malloc, pipe, open error		:	EXECUTION_FAILUE
// success						:	fd
static int	here_document_to_fd(t_redirect *r, t_shell_env *shell_env)
{
	int		herepipe[2];
	size_t	document_len;
	int		fd;

	document_len = 0;
	if (r->redirectee.filename->word && !heredoc_expand(r, &document_len,
			shell_env))
		return (fatal_error("malloc", MALLOC_ERR_STR), EXECUTION_FAILURE);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
		{
			return (sys_error("open failed"), EXECUTION_FAILURE);
		}
		return (fd);
	}
	else if (document_len <= HEREDOC_PIPESIZE)
	{
		if (pipe(herepipe) < 0)
			return (sys_error("pipe failed"), EXECUTION_FAILURE);
		ft_dprintf(herepipe[1], "%s", r->redirectee.filename->word);
		close(herepipe[1]);
		return (herepipe[0]);
	}
	else
		return (here_document_to_file(r));
}

// static int	do_redirection_internal(t_redirect *r)
// {
// 	int	fd;
// 	int	to_fd;

// 	while (r)
// 	{
// 		if (r->instruction == r_input_direction)
// 		{
// 			fd = open(r->redirectee.filename->word, O_RDONLY);
// 			to_fd = STDIN_FILENO;
// 		}
// 		else
// 		{
// 			fd = open(r->redirectee.filename->word, r->flags, 0666);
// 			to_fd = STDOUT_FILENO;
// 		}
// 		if (fd < 0)
// 			return (fatal_error(r->redirectee.filename->word, strerror(errno)),
// 				EXECUTION_FAILURE); // ### TODO: エラー処理
// 		if (dup2(fd, to_fd) < 0)
// 			return (sys_error("dup2 failed"), EXECUTION_FAILURE);
// 				// ### TODO: エラー処理
// 		close(fd);
// 		r = r->next;
// 	}
// 	return (EXECUTION_SUCCESS);
// }

static int	do_redirection_internal(t_redirect *r)
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
				EXECUTION_FAILURE); // ### TODO: エラー処理
	if (dup2(fd, to_fd) < 0)
		return (sys_error("dup2 failed"), EXECUTION_FAILURE);
	// ### TODO: エラー処理
	close(fd);
	return (EXECUTION_SUCCESS);
}

// int	do_redirections(t_redirect *redir, t_shell_env *shell_env)
// {
// 	int here_fd;

// 	if (redir->instruction == r_input_direction
// 		|| redir->instruction == r_output_direction
// 		|| redir->instruction == r_appending_to)
// 		if (do_redirection_internal(redir) == EXECUTION_FAILURE)
// 			return (EXECUTION_FAILURE);
// 	if (redir->instruction == r_reading_until)
// 	{
// 		here_fd = here_document_to_fd(redir, shell_env);
// 		if (here_fd == EXECUTION_FAILURE)
// 			return (EXECUTION_FAILURE);
// 		if (dup2(here_fd, STDIN_FILENO) < 0)
// 			return (EXECUTION_FAILURE);
// 	}
// 	return (EXECUTION_SUCCESS);
// }

int	do_redirections(t_redirect *redir, t_shell_env *shell_env)
{
	int here_fd;

	while (redir)
	{
		if (redir->instruction == r_input_direction
			|| redir->instruction == r_output_direction
			|| redir->instruction == r_appending_to)
		{
			if (do_redirection_internal(redir) == EXECUTION_FAILURE)
				return (EXECUTION_FAILURE);
		}
		else if (redir->next && redir->instruction == r_reading_until
			&& redir->next->instruction == r_reading_until)
		{
			redir = redir->next;
			continue ;
		}
		else
		{
			here_fd = here_document_to_fd(redir, shell_env);
			if (here_fd == EXECUTION_FAILURE)
				return (EXECUTION_FAILURE);
			if (dup2(here_fd, STDIN_FILENO) < 0)
				return (EXECUTION_FAILURE);
		}
		redir = redir->next;
	}
	return (EXECUTION_SUCCESS);
}