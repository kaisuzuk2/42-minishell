/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:23:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/17 14:08:52 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expand(t_redirect *r, size_t *lenp)
{
	if (r->redirectee.filename->flag != W_SQUOTE && r->redirectee.filename->flag != W_DQUOTE && ft_strchr(r->redirectee.filename->word, '$'))
		r->redirectee.filename->word = expand_string_to_string(r->redirectee.filename->word);
	if (r->redirectee.filename->word)
		*lenp = ft_strlen(r->redirectee.filename->word);
	return (r->redirectee.filename->word);
}

static char	*documentcat(char *document, char *buf)
{
	char	*tmp;

	if (!document)
	{
		document = ft_strdup(buf);
		if (!document)
			return (NULL);
	}
	else
	{
		tmp = ft_strjoin(document, buf);
		free(document);
		if (!tmp)
			return (NULL);
		document = tmp;
	}
	return (document);
}

static t_bool	is_heredoc_eof(char *here_doc_eof, char *buf)
{
	if (ft_strncmp(buf, here_doc_eof, ft_strlen(here_doc_eof)) == 0)
	{
		free(buf);
		return (TRUE);
	}
	return (FALSE);
}

char	*make_here_document(t_redirect *r)
{
	char	*buf;
	char	*document;

	document = NULL;
	while (1)
	{
		buf = readline("> "); // ### TODO: プロンプトは$PS2
		if (!buf)
			break ;
		if (is_heredoc_eof(r->here_doc_eof, buf))
			break ;
		document = documentcat(document, buf);
		document = documentcat(document, "\n");
		free(buf);
		if (!document)
		{
			// dispose_command(c);
			// sys_error(MALLOC_STR);
			exit(EXECUTION_FAILURE); // ### TODO: エラー処理
		}
	}
	return (document);
}