/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/12/09 12:45:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser_utils.c
t_bool				is_unexpected_token(t_command *cmd, t_token_list *token);
t_command			*new_command(t_command_type type);

// parser_redirect.c
t_redirect			*connect_redirection(t_command *command,
						t_token_list **token_p, t_token_error *e);

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
	if (!desc)
		return (free(list), NULL);
	*token_p = token->next;
	list->word = desc;
	if (!command->words)
	{
		command->words = list;
		return (list);
	}
	cur = command->words;
	while (cur->next)
		cur = cur->next;
	cur->next = list;
	return (list);
}

static t_command	*make_simple_command(t_token_list **token_p,
		t_token_list *token, t_token_error *e)
{
	t_command	*command;

	command = new_command(CM_SIMPLE);
	if (!command)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	while (!is_eoftoken(token->word->kind) && !is_pipetoken(token->word->kind))
	{
		if (is_wordtoken(token->word->kind))
		{
			if (!append_command_words(command, &token, token))
				set_parse_error(ST_ERR_NOMEM, NULL, NULL, e);
		}
		else if (is_redirect(token->word->kind)
			&& !is_eoftoken(token->next->word->kind))
			connect_redirection(command, &token, e);
		else
			set_parse_error(ST_ERR_SYNTAX, PARSE_ERR_STR, token->word->word, e);
		if (e->status != ST_OK)
			return (dispose_simple_command(command), NULL);
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
		set_parse_error(ST_ERR_SYNTAX, PARSE_ERR_STR, (*token_p)->word->word,
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

static t_command	*add_command(t_command *cur, t_token_list **token_p,
		t_token_list *token, t_token_error *e)
{
	if (is_unexpected_token(cur, token))
		return (set_parse_error(ST_ERR_SYNTAX, PARSE_ERR_STR, token->word->word,
				e), NULL);
	if (is_wordtoken(token->word->kind) || is_redirect(token->word->kind))
	{
		cur->command = make_simple_command(token_p, token, e);
		if (!cur->command)
			return (NULL);
	}
	else if (is_pipetoken(token->word->kind))
		return (make_connection_command(cur, token_p, CM_CONNECTION, e));
	return (cur);
}

t_command	*parser(t_token_list *token, t_shell_env *shell_env)
{
	t_token_error	e;
	t_command		*head;
	t_command		*cur;
	t_token_list	*token_p;

	token_p = token;
	head = new_command(CM_CONNECTION);
	if (!head)
	{
		dispose_token_words(token_p);
		dispose_env(shell_env);
		exit(EX_FATAL_ERROR);
	}
	cur = head;
	cur->head = head;
	while (token && !is_eoftoken(token->word->kind))
	{
		ft_memset(&e, 0, sizeof(e));
		cur = add_command(cur, &token, token, &e);
		if (handle_parse_error(&e, token_p, head, shell_env))
			return (NULL);
		cur->head = head;
	}
	dispose_token_words(token_p);
	return (head);
}
