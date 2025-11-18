/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:23:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 17:03:40 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make_cmd_utils.c
t_bool			is_hasdollar(t_word_desc *desc);
t_bool			is_d_quote(t_word_desc *desc);
t_bool			is_s_quote(t_word_desc *desc);

char	*heredoc_expand(t_redirect *r, size_t *lenp, t_shell_env *shell_env)
{
	t_word_desc	*heredoc_desc;

	heredoc_desc = r->redirectee.filename;
	if (!is_s_quote(heredoc_desc) && !is_d_quote(heredoc_desc)
		&& ft_strchr(heredoc_desc->word, '$'))
		heredoc_desc->word = expand_string_to_string(heredoc_desc->word,
				heredoc_desc->word, shell_env);
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

static t_bool	read_here_document(char **document, char *here_doc_eof,
		t_token_error *e)
{
	char	*buf;

	while (1)
	{
		buf = readline(PS2);
		if (!buf)
			break ;
		if (*buf == '\0' && g_signal_state == SIGSTATE_INT)
		{
			g_signal_state = SIGSTATE_NONE;
			free(*document);
			set_parse_error(ST_SIGNAL, NULL, NULL, e);
			return (FALSE);
		}
		if (is_heredoc_eof(here_doc_eof, buf))
			break ;
		*document = documentcat(*document, buf);
		*document = documentcat(*document, "\n");
		free(buf);
		if (!*document)
			return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), FALSE);
	}
	return (TRUE);
}

char	*make_here_document(char *here_doc_eof, t_token_error *e)
{
	char	*buf;
	char	*document;

	g_signal_state = SIGSTATE_NONE;
	enter_heredoc_mode();
	document = strdup("");
	if (!document)
		return (fatal_error("malloc", MALLOC_ERR_STR),
			set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	if (!read_here_document(&document, here_doc_eof, e))
		return (NULL);
	enter_prompt_mode();
	if (e->status != ST_OK)
		return (NULL);
	return (document);
}
