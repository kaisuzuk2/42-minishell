/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/25 16:22:35 by kaisuzuk         ###   ########.fr       */
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

static t_bool	is_redirect(t_token_kind kind)
{
	return (kind == TK_GREAT_GREAT || kind == TK_GREAT || kind == TK_LESS_LESS
		|| kind == TK_LESS);
}

// setting local errno
static t_command	*make_simple_command(t_token_list **token_p,
		t_token_list *token, t_token_error *e)
{
	t_command		*command;

	command = new_command(CM_SIMPLE);
	if (!command) // TODO: エラー処理
		return (e->status = ST_ERR_NOMEM, NULL);
	while (token->word->kind != TK_EOF && token->word->kind != TK_PIPE)
	{
		if (token->word->kind == TK_WORD)
		{
			if (!append_command_words(command, &token))
				return (dispose_simple_command(command),
					e->status = ST_ERR_NOMEM, NULL);
		}
		else if (is_redirect(token->word->kind) && token->next->word->kind == TK_WORD)
		{
			if (!connect_redirection(command, &token))
				return (dispose_simple_command(command),
					e->status = ST_ERR_NOMEM, NULL);
		}
		else
			return (dispose_simple_command(command), e->status = ST_ERR_SYNTAX,
				e->msg = PARSE_ERROR_STR, e->detail = "newline", NULL);
	}
	*token_p = token;
	return (command);
}

// t_command	*parser(t_token_list *token)
// {
// 	t_command		*head;
// 	t_command		*cur;
// 	t_token_error	e;

// 	head = new_command(CM_CONNECTION);
// 	if (!head)
// 		return (NULL);
// 	cur = head;
// 	memset(&e, 0, sizeof(e));
// 	while (token && token->word->kind != TK_EOF)
// 	{
// 		memset(&e, 0, sizeof(e));
// 		if (token->word->kind != TK_PIPE)
// 		{
// 			cur->command = make_simple_command(&token, token, &e);
// 			if (!cur->command)
// 				break ;
// 		}
// 		else
// 		{
// 			cur->next = new_command(CM_CONNECTION);
// 			if (!cur->next)
// 				break ;
// 			cur = cur->next;
// 			token = token->next;
// 		}
// 	}
// 	if (e.status != ST_OK)
// 	{
// 		dispose_command(head);
// 		if (e.status == ST_ERR_NOMEM)
// 			exit(1);
// 		return (parser_operator_error(e.msg, e.detail), NULL);

// 	}
// 	return (head);
// }

// t_command *add_command(t_command *cur, t_token_list **token_p, t_token_list *token, t_token_error *e)
// {
// 	t_command *connect_com;
// 	t_command *simple_com;

// 	if (!cur->command && token->word->kind == TK_PIPE)
// 		return (e->status = ST_ERR_SYNTAX, e->msg = PARSE_ERROR_STR, e->detail = token->word->word, NULL);
// 	if (token->word->kind == TK_WORD)
// 	{
// 		simple_com = make_simple_command(token_p, token, e);
// 		if (!simple_com)
// 			return (NULL);
// 		cur->command = simple_com;
// 	}
// 	if (token->word->kind == TK_PIPE)
// 	{
// 		connect_com = new_command(CM_CONNECTION);
// 		if (!connect_com)
// 			return (dispose_simple_command(simple_com), NULL);
// 		cur->next = connect_com;
// 	}
// }

static t_command *make_connection_command(t_command *cur, t_token_list **token_p, t_command_type type, t_token_error *e)
{
	t_command *new;

	if (!cur->command)
		return (e->status = ST_ERR_SYNTAX, e->msg = PARSE_ERROR_STR, e->detail = (*token_p)->word->word, NULL);
	new = new_command(type);
	if (!new)
		return (e->status = ST_ERR_NOMEM, NULL);
	cur->next = new;
	(*token_p) = (*token_p)->next;
	return new;
}

static t_command *add_command(t_command *cur, t_token_list **token_p, t_token_list *token, t_token_error *e)
{
	if (!cur->command && token->word->kind == TK_PIPE)
		return (e->status = ST_ERR_SYNTAX, e->msg = PARSE_ERROR_STR, e->detail = token->word->word, NULL);
	if (token->word->kind == TK_WORD)
		cur->command = make_simple_command(token_p, token, e);
	if (token->word->kind == TK_PIPE && token->next->word->kind == TK_EOF)
		return (e->status = ST_ERR_SYNTAX, e->msg = PARSE_ERROR_STR, e->detail = token->word->word, NULL);
	if (token->word->kind == TK_PIPE)
		return (make_connection_command(cur, token_p, CM_CONNECTION, e));
	return (cur);
}

static int parse_error(t_token_error *e, t_token_list *token, t_command *command)
{
	if (e->status == ST_OK)
		return (0);
	if (e->status == ST_ERR_SYNTAX)
		parser_operator_error(e->msg, e->detail);
	dispose_token_words(token);
	dispose_command(command);
	if (e->status == ST_ERR_NOMEM)
		exit (1);
	return (1);
}

t_command *parser(t_token_list *token)
{
	t_token_error e;
	t_command *head;
	t_command *cur;

	head = (t_command *)xmalloc(sizeof(t_command));
	if (!head)
	{
		dispose_token_words(token);
		exit (1);
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

// t_command *parser(t_token_list *token)
// {
// 	t_token_error e;
// 	t_command *head;
// 	t_command *cur;

// 	head = (t_command *)xmalloc(sizeof(t_command));
// 	if (!head)
// 	{
// 		dispose_desc_words(token);
// 		exit(1);
// 	}
// 	cur = head;
// 	while (token && token->word->kind != TK_EOF)
// 	{
// 		cur = add_command(cur, &token, token , &e);
// 		if (!cur)
// 		{
// 			dispose_desc_words(token);
// 			dispose_command(head);
// 			if (e.status == ST_ERR_NOMEM)
// 				exit (1);
// 			return (parser_operator_error(e.msg, e.detail), NULL);
// 		}
// 	}
// 	return (head);
// }