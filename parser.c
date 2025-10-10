/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/10 12:58:04 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word_desc *tokendup(t_word_desc *desc)
{
	t_word_desc *new;

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

static t_command	*append_command_words(t_command *command, t_word_desc *desc)
{
	t_word_list	*list;
	t_word_list	*cur;

	list = (t_word_list *)ft_calloc(sizeof(t_word_list), 1);
	if (!list)
		return (NULL);
	if (!command->words)
	{
		list->word = tokendup(desc); // ### TODO: エラー処理
		command->words = list;
		return (command);
	}
	cur = command->words;
	while (cur->next)
		cur = cur->next;
	list = (t_word_list *)ft_calloc(sizeof(t_word_list), 1);
	list->word = tokendup(desc); // ### TODO: エラー処理
	cur->next = list;
	return (command);
}

static t_command *make_simple_command(t_token_list **token)
{
	t_command *command;
	t_token_list *cur_token;

	cur_token = *token;
	command = new_command(CM_SIMPLE);
	if (!command) // TODO: エラー処理
		return (NULL);
	while (cur_token->word->kind != TK_EOF && cur_token->word->kind == TK_WORD)
	{
		append_command_words(command, cur_token->word); // ### TODO: エラー処理
		cur_token = cur_token->next;
	}
	append_command_words(command, NULL);
	*token = cur_token;
	return (command);
}

t_command *connection(t_token_list *token)
{
	t_command *command;
	t_command *head;
	t_command *cur;

	command = new_command(CM_CONNECTION);
	head = command;
	cur = command;
	if (!command) // ### TODO: エラー処理考
		return (NULL);
	while (token && token->word->kind != TK_EOF)
	{
		if (token->word->kind == TK_WORD)
			cur->command = make_simple_command(&token); // ### TODO: エラー処理
		else
		{
			cur->next = new_command(CM_CONNECTION);
			token = token->next;
			cur = cur->next;
		}
	}
	cur->next = ft_calloc(sizeof(t_command), 1);
	return (head);
}

t_command	*parser(t_token_list *token)
{
	return (connection(token));
}
