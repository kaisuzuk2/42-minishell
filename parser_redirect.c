/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:48:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/24 13:45:57 by kaisuzuk         ###   ########.fr       */
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

t_redirect	*make_redirection(t_token_list **token)
{
	t_redirect	*redirect;
	int			i;

	const t_redirect_info redirect_info_table[] = {
		{TK_LESS, r_input_direction, O_RDONLY},
		{TK_LESS_LESS, r_reading_until, 0},
		{TK_GREAT, r_output_direction, O_WRONLY | O_CREAT | O_TRUNC},
		{TK_GREAT_GREAT, r_appending_to, O_WRONLY | O_CREAT | O_APPEND},
	};
	redirect = (t_redirect *)xcalloc(sizeof(t_redirect), 1);
	if (!redirect) // ### TODO: エラー処理
		return (NULL);
	i = 0;
	while (i < sizeof(redirect_info_table) / sizeof(redirect_info_table[0]))
	{
		if ((*token)->word->kind == redirect_info_table[i].kind)
			set_redirect(redirect, redirect_info_table[i], (*token)->next);
		i++;
	}
	// tokenに一致しない場合の処理どうする？
	*token = (*token)->next->next;
	return (redirect);
}