/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:23:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/07 11:13:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expand(t_redirect *r, size_t *lenp, t_varlist *env)
{
	if (!is_s_quote(r->redirectee.filename)
		&& !is_d_quote(r->redirectee.filename)
		&& ft_strchr(r->redirectee.filename->word, '$'))
		// ### TODO: is_hasdollar?
		r->redirectee.filename->word = expand_string_to_string(env,
				r->redirectee.filename->word);
	if (r->redirectee.filename->word)
		*lenp = ft_strlen(r->redirectee.filename->word);
	return (r->redirectee.filename->word);
}

static char	*documentcat(char *document, char *buf)
{
	char	*tmp;

	if (!document || *document == '\0')
	{
		free(document);
		document = ft_strdup(buf);
		if (!document)
			return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	}
	else
	{
		tmp = ft_strjoin(document, buf);
		free(document);
		if (!tmp)
			return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
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

char	*make_here_document(char *here_doc_eof, t_token_error *e)
{
	char *buf;
	char *document;

	g_signal_state = SIGSTATE_NONE;
	enter_heredoc_mode();
	document = strdup("");
	if (!document)
		return (fatal_error("malloc", MALLOC_ERR_STR), set_parse_error(ST_ERR_NOMEM, NULL, NULL, e),  NULL);
	while (1)
	{
		buf = readline("> "); // ### TODO: プロンプトは$PS2
		if (!buf)
			break;
		if (*buf == '\0' && g_signal_state == SIGSTATE_INT)
		{
			g_signal_state = SIGSTATE_NONE;
			free(document);
			set_parse_error(ST_SIGNAL, NULL, NULL, e);
			break;
		}
		if (is_heredoc_eof(here_doc_eof, buf))
			break ;
		document = documentcat(document, buf);
		document = documentcat(document, "\n"); // ### TODO: もう少し考える
		free(buf);
		if (!document)
			return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	}
	enter_prompt_mode();
	if (e->status != ST_OK)
		return (NULL);
	return (document);
}