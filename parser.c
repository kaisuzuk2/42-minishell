/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/25 18:27:22 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser_redirect.c
t_bool				set_redirect(t_redirect *redir, t_redirect_info info,
						t_token_list *token);

// parser_utils.c
t_word_desc			*tokendup(t_word_desc *desc);
t_command			*new_command(t_command_type type);
t_bool				is_redirect(t_token_kind kind);
int					parse_error(t_token_error *e, t_token_list *token,
						t_command *command);
t_redirect			*connect_redirection(t_command *command,
						t_token_list **token);
void				set_parse_error(t_token_status status, const char *msg,
						const char *detail, t_token_error *e);

static t_word_list	*append_command_words(t_command *command,
		t_token_list **token_p, t_token_list *token)
{
	t_word_list	*list;
	t_word_list	*cur;
	t_word_desc	*desc;

	list = (t_word_list *)xcalloc(sizeof(t_word_list), 1);
	if (!list)
		return (NULL);
	desc = tokendup(token->word);
	*token_p = token->next;
	if (!token)
		return (free(list), NULL);
	list->word = desc;
	if (!command->words)
		return (command->words = list, list);
	cur = command->words;
	while (cur->next)
		cur = cur->next;
	cur->next = list;
	return (list);
}

// setting local errno
static t_command	*make_simple_command(t_token_list **token_p,
		t_token_list *token, t_token_error *e)
{
	t_command	*command;

	command = new_command(CM_SIMPLE);
	if (!command)
		return (e->status = ST_ERR_NOMEM, NULL);
	while (token->word->kind != TK_EOF && token->word->kind != TK_PIPE)
	{
		if (token->word->kind == TK_WORD)
		{
			if (!append_command_words(command, &token, token))
				return (dispose_simple_command(command),
					set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
		}
		else if (is_redirect(token->word->kind)
			&& token->next->word->kind == TK_WORD)
		{
			if (!connect_redirection(command, &token))
				return (dispose_simple_command(command),
					set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
		}
		else
			return (dispose_simple_command(command),
				set_parse_error(ST_ERR_SYNTAX, PARSE_ERROR_STR,
					token->word->word, e), NULL);
	}
	*token_p = token;
	return (command);
}

static t_command	*make_connection_command(t_command *cur,
		t_token_list **token_p, t_command_type type, t_token_error *e)
{
	t_command	*new;

	if (!cur->command)
	{
		set_parse_error(ST_ERR_SYNTAX, PARSE_ERROR_STR, (*token_p)->word->word,
			e);
		return (NULL);
	}
	new = new_command(type);
	if (!new)
	{
		set_parse_error(ST_ERR_NOMEM, NULL, NULL, e);
		return (NULL);
	}
	cur->next = new;
	(*token_p) = (*token_p)->next;
	return (new);
}

// Validation	: 	[ | ls  ] [ ls | ]
static t_command	*add_command(t_command *cur, t_token_list **token_p,
		t_token_list *token, t_token_error *e)
{
	if (!cur->command && token->word->kind == TK_PIPE)
	{
		set_parse_error(ST_ERR_SYNTAX, PARSE_ERROR_STR, token->word->word, e);
		return (NULL);
	}
	if (token->word->kind == TK_PIPE && token->next->word->kind == TK_EOF)
	{
		set_parse_error(ST_ERR_SYNTAX, PARSE_ERROR_STR, token->word->word, e);
		return (NULL);
	}
	if (token->word->kind == TK_WORD)
		cur->command = make_simple_command(token_p, token, e);
	if (token->word->kind == TK_PIPE)
		return (make_connection_command(cur, token_p, CM_CONNECTION, e));
	return (cur);
}

t_command	*parser(t_token_list *token)
{
	t_token_error	e;
	t_command		*head;
	t_command		*cur;

	head = (t_command *)xmalloc(sizeof(t_command));
	if (!head)
	{
		dispose_token_words(token);
		exit(1);
	}
	cur = head;
	while (token && token->word->kind != TK_EOF)
	{
		memset(&e, 0, sizeof(e));
		cur = add_command(cur, &token, token, &e);
		if (parse_error(&e, token, head))
			return (NULL);
	}
	return (head);
}
