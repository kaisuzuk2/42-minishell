/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:14:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 10:21:04 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make_cmd.cmake make
char		*heredoc_expand(t_redirect *r, size_t *lenp,
				t_shell_env *shell_env);

// ft_mkstemp.c
int	ft_mkstemp(char **template);


static int	sh_mktmpfd(const char *nameroot, char **filename)
{
	*filename = ft_strjoin("/tmp/", nameroot);
	if (!*filename)
		return (internal_error("malloc", MALLOC_ERR_STR), EXECUTION_MEMERR);
	return (ft_mkstemp(filename));
}

static int	here_document_to_file(t_redirect *r)
{
	int		fd;
	int		fd2;
	char	*filename;

	fd = sh_mktmpfd("sh-thd", &filename);
	if (fd < 0)
		return (fd);
	ft_dprintf(fd, "%s", r->redirectee.filename->word);
	close(fd);
	fd2 = open(filename, O_RDONLY, 0600);
	if (fd2 < 0)
	{
		internal_error(filename, strerror(errno));
		unlink(filename);
		free(filename);
		return (EXECUTION_ERR);
	}
	if (unlink(filename) < 0)
	{
		close(fd2);
		free(filename);
		return (sys_error("unlink failed"), EXECUTION_ERR);
	}
	return (free(filename), fd2);
}

int	here_document_to_fd(t_redirect *r, t_shell_env *shell_env)
{
	int		herepipe[2];
	size_t	document_len;
	int		fd;

	document_len = 0;
	if (r->redirectee.filename->word && !heredoc_expand(r, &document_len,
			shell_env))
		return (fatal_error("malloc", MALLOC_ERR_STR), EXECUTION_MEMERR);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return (sys_error("open failed"), EXECUTION_ERR);
		return (fd);
	}
	else if (document_len <= HEREDOC_PIPESIZE)
	{
		if (pipe(herepipe) < 0)
			return (sys_error("pipe failed"), EXECUTION_ERR);
		ft_dprintf(herepipe[1], "%s", r->redirectee.filename->word);
		close(herepipe[1]);
		return (herepipe[0]);
	}
	else
		return (here_document_to_file(r));
}
