/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/17 14:01:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word_desc	*tokendup(t_word_desc *desc)
{
	t_word_desc	*new;

	new = (t_word_desc *)malloc(sizeof(t_word_desc));
	if (!new)
		return (NULL);
	if (!desc)
		new->word = NULL;
	else
		new->word = ft_strdup(desc->word);
	if (!new->word)
		return (free(new), NULL);
	new->kind = desc->kind;
	new->flag = desc->flag;
	return (new);
}

static t_command	*new_command(t_command_type type)
{
	t_command	*command;

	command = (t_command *)ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->type = type;
	return (command);
}

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

// <
static void	input_redirect(t_redirect *redirect, t_token_list *token)
{
	redirect->instruction = r_input_direction;
	redirect->redirectee.filename = tokendup(token->word); // ### TODO: エラー処理
	redirect->flags = O_RDONLY;
	redirect->redirector.dest = STDIN_FILENO;
}

// >
static void output_redirect(t_redirect *redirect ,t_token_list *token)
{
	redirect->instruction = r_output_direction;
	redirect->redirectee.filename = tokendup(token->word);
	redirect->flags = O_WRONLY | O_CREAT | O_TRUNC;
	redirect->redirector.dest = STDOUT_FILENO;
}

// >>
static void append_redirect(t_redirect *redirect, t_token_list *token)
{
	redirect->instruction = r_appending_to;
	redirect->redirectee.filename = tokendup(token->word);
	redirect->flags = O_WRONLY | O_CREAT | O_APPEND;
	redirect->redirector.dest = STDOUT_FILENO;
}

// <<
static void heredoc_redirect(t_redirect *redirect, t_token_list *token)
{
	redirect->instruction = r_reading_until;
	redirect->here_doc_eof = savestring(token->word->word);
	redirect->redirectee.filename = (t_word_desc *)malloc(sizeof(t_word_desc));
	redirect->redirectee.filename->word = make_here_document(redirect); // ### TODO: エラー処理
	redirect->redirectee.filename->flag = token->word->flag;
}

static t_redirect	*make_redirection(t_token_list **token)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)ft_calloc(sizeof(t_redirect), 1);
	if (!redirect) // ### TODO: エラー処理
		return (NULL);
	if ((*token)->word->kind == TK_LESS)
		input_redirect(redirect, (*token)->next);
	else if ((*token)->word->kind == TK_LESS_LESS)
		heredoc_redirect(redirect, (*token)->next);
	else if ((*token)->word->kind == TK_GREAT)
		output_redirect(redirect, (*token)->next);
	else if ((*token)->word->kind == TK_GREAT_GREAT)
		append_redirect(redirect, (*token)->next);
	*token = (*token)->next->next;
	return (redirect);
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

static t_command	*make_simple_command(t_token_list **token_p, t_token_list *token)
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
	while (token->word->kind != TK_EOF)
	{
		kind = token->word->kind;
		if (kind == TK_WORD)
		{
			list = append_command_words(command, &token); // ### TODO: エラー処理
			if (!list)
			{
				if (redir)
					dispose_redirects(redir);
				free(command);
				return (NULL);
			}
		}
		else if ((kind == TK_GREAT_GREAT || kind == TK_GREAT
				|| kind == TK_LESS_LESS || kind == TK_LESS)
			&& token->next->word->kind == TK_WORD)
		{
			redir = connect_redirection(command, &token);
			if (!redir)
			{
				if (list)
					dispose_desc_words(list);
				free(command);
				return (NULL);
			}
		}
		else
		{
			printf("Syntax Error\n"); //### TODO: エラー処理
			if (list)
				dispose_desc_words(list);
			if (redir)
				dispose_redirects(redir);
			free(command);
			return (NULL);
		}
		kind = token->word->kind;
	}
	*token_p = token;
	return (command);
}

t_command	*connection(t_token_list *token)
{
	t_command	*head;
	t_command	*cur;
	t_command *t;
	t_redirect	*cur_redir;

	head = new_command(CM_CONNECTION);
	if (!head) // ### TODO: エラー処理
		return (NULL);
	cur = head;
	while (token && token->word->kind != TK_EOF)
	{
		if (token->word->kind != TK_PIPE)
		{
			t = make_simple_command(&token, token); // ### TODO: エラー処理
			if (!t)
				return (dispose_command(head), NULL);
			cur->command = t;
		}
		else
		{
			t = new_command(CM_CONNECTION); // ### TODO: エラー処理
			if (!t)
				return (dispose_command(head), NULL);
			cur->next = t;
			token = token->next;
			cur = cur->next;
		}
	}
	cur->words = ft_calloc(sizeof(t_word_list), 1);
	return (head);
}

t_command	*parser(t_token_list *token)
{
	return (connection(token));
}
