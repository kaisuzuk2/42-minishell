/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/25 12:58:08 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser_redirect.c
t_bool				set_redirect(t_redirect *redir, t_redirect_info info,
						t_token_list *token);
t_redirect			*make_redirection(t_token_list **token);

// parser_utils.c
t_word_desc			*tokendup(t_word_desc *desc);
t_command			*new_command(t_command_type type);

// comman->t_word_list +
static t_word_list	*append_command_words(t_command *command,
		t_token_list **token)
{
	t_word_list	*list;
	t_word_list	*cur;

	list = (t_word_list *)ft_calloc(sizeof(t_word_list), 1);
	if (!list)
		return (NULL);
	if (!command->words)
	{
		list->word = tokendup((*token)->word); // ### TODO: エラー処理
		command->words = list;
		*token = (*token)->next;
		return (list);
	}
	cur = command->words;
	while (cur->next)
		cur = cur->next;
	list = (t_word_list *)ft_calloc(sizeof(t_word_list), 1);
	list->word = tokendup((*token)->word); // ### TODO: エラー処理
	cur->next = list;
	*token = (*token)->next;
	return (list);
}

static t_redirect	*connect_redirection(t_command *command,
		t_token_list **token)
{
	t_redirect	*cur_redir;

	if (!command->redirects)
		command->redirects = make_redirection(token); // ### TODO: エラー処理
	else
	{
		cur_redir = command->redirects;
		while (cur_redir->next)
			cur_redir = cur_redir->next;
		cur_redir->next = make_redirection(token); // ### TODO: エラー処理
	}
}

static t_command	*make_simple_command(t_token_list **token_p,
		t_token_list *token)
{
	t_command		*command;
	t_word_list		*list;
	t_redirect		*redir;
	t_token_kind	kind;

	list = NULL;
	redir = NULL;
	command = new_command(CM_SIMPLE);
	if (!command) // TODO: エラー処理
		return (NULL);
	while (token->word->kind != TK_EOF && token->word->kind != TK_PIPE)
	{
		kind = token->word->kind;
		if (kind == TK_WORD)
		{
			if (!append_command_words(command, &token))
				return (dispose_simple_command(command), NULL);
		}
		else if ((kind == TK_GREAT_GREAT || kind == TK_GREAT
				|| kind == TK_LESS_LESS || kind == TK_LESS)
			&& token->next->word->kind == TK_WORD)
		{
			if (!connect_redirection(command, &token))
				return (dispose_simple_command(command), NULL);
		}
		else
		{
			return (parser_operator_error(PARSE_ERROR_STR, "newline"),
				dispose_simple_command(command), NULL);
		}
	}
	*token_p = token;
	return (command);
}

t_command	*parser(t_token_list *token)
{
	t_command	*head;
	t_command	*cur;
	t_redirect	*cur_redir;

	head = new_command(CM_CONNECTION);
	if (!head)
		return (NULL);
	cur = head;
	while (token && token->word->kind != TK_EOF)
	{
		if (token->word->kind != TK_PIPE)
		{
			cur->command = make_simple_command(&token, token);
			if (!cur->command)
				return (dispose_command(head), NULL);
		}
		else
		{
			cur->next = new_command(CM_CONNECTION);
			if (!cur->next)
				return (dispose_command(head), NULL);
			cur = cur->next;
			token = token->next;
		}
	}
	return (head);
}
