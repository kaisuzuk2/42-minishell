/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:48:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/12/07 13:57:19 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expand_quote_removal.c
char				*quote_removal_delimiter(char *delimiter);

// make_cmd.c
char				*make_here_document(char *here_doc_eof, t_token_error *e);

static t_bool	set_heredoc(t_redirect *redir, t_word_desc *desc,
		t_token_error *e)
{
	redir->here_doc_eof = quote_removal_delimiter(desc->word);
	if (!redir->here_doc_eof)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), FALSE);
	redir->redirectee.filename = (t_word_desc *)xmalloc(sizeof(t_word_desc));
	if (!redir->redirectee.filename)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), FALSE);
	redir->redirectee.filename->word = make_here_document(redir->here_doc_eof,
			e);
	if (!redir->redirectee.filename->word)
		return (FALSE);
	redir->redirectee.filename->flag = desc->flag;
	return (TRUE);
}

static t_bool	set_redirect(t_redirect *redir, t_redirect_info info,
		t_token_list *token, t_token_error *e)
{
	redir->instruction = info.instruction;
	if (info.instruction == r_reading_until)
		return (set_heredoc(redir, token->word, e));
	redir->redirectee.filename = tokendup(token->word);
	if (!redir->redirectee.filename)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), FALSE);
	redir->flags = info.flag;
	return (TRUE);
}

static t_redirect	*make_redirection(t_token_list **token, t_token_error *e)
{
	t_redirect				*redirect;
	unsigned long long int	i;
	const t_redirect_info	redir_table[] = {
	{TK_LESS, r_input_direction, O_RDONLY},
	{TK_LESS_LESS, r_reading_until, 0},
	{TK_GREAT, r_output_direction, O_WRONLY | O_CREAT | O_TRUNC},
	{TK_GREAT_GREAT, r_appending_to, O_WRONLY | O_CREAT | O_APPEND},
	};

	redirect = (t_redirect *)xcalloc(sizeof(t_redirect), 1);
	if (!redirect)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	i = 0;
	while (i < sizeof(redir_table) / sizeof(redir_table[0]))
	{
		if ((*token)->word->kind == redir_table[i].kind)
		{
			if (!set_redirect(redirect, redir_table[i], (*token)->next, e))
				return (NULL);
			break ;
		}
		i++;
	}
	*token = (*token)->next->next;
	return (redirect);
}

t_redirect	*connect_redirection(t_command *command, t_token_list **token_p,
		t_token_error *e)
{
	t_redirect	*new;
	t_redirect	*cur;

	new = make_redirection(token_p, e);
	if (!new)
		return (NULL);
	if (!command->redirects)
		command->redirects = new;
	else
	{
		cur = command->redirects;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}
