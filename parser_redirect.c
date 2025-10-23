/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:48:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/23 14:32:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser_utils.c
t_word_desc	*tokendup(t_word_desc *desc);

static t_bool set_heredoc(t_redirect *redir, t_word_desc *desc)
{
	redir->here_doc_eof = savestring(desc->word);
	if (!redir->here_doc_eof)
		return (fatal_error("malloc", MALLOC_ERROR_STR), FALSE);
	redir->redirectee.filename = (t_word_desc *)xmalloc(sizeof(t_word_desc));
	if (!redir->redirectee.filename)
		return (fatal_error("malloc", SYNTAX_ERROR_STR), FALSE);
	redir->redirectee.filename->word = make_here_document(redir->here_doc_eof);
	if (!redir->redirectee.filename->word)
		return (FALSE);
	redir->redirectee.filename->flag = desc->flag;
	return (TRUE);
}

t_bool set_redirect(t_redirect *redir, t_redirect_info info, t_token_list *token)
{
	redir->instruction = info.instruction;
	if (info.instruction == r_reading_until)
		return (set_heredoc(redir, token->word));
	redir->redirectee.filename = tokendup(token->word); 
	if (!redir->redirectee.filename)
		return (fatal_error("malloc", MALLOC_ERROR_STR) ,FALSE);
	redir->flags = info.flag;
	return (TRUE);
}