/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/08 15:16:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word_desc *tokendup(t_word_desc *desc)
{
	t_word_desc *new;

	new = (t_word_desc *)malloc(sizeof(t_word_desc));
	if (!new)
		return (NULL);
	new->word = ft_strdup(desc->word);
	if (!new->word)
		return (free(new), NULL);
	new->kind = desc->kind;
	new->flag = desc->flag;
}

static t_command	*new_command(t_command type)
{
	t_command	*command;

	command = (t_command *)ft_calloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->type = type;
	return (command);
}

static t_command	*append_command_words(t_command *command, t_word_desc *desc)
{
	t_word_list	*list;
	t_word_list	*cur;

	list = (t_word_list *)ft_calloc(sizeof(t_word_list));
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
	list = (t_word_list *)ft_calloc(sizeof(t_word_list));
	list->word = tokendup(desc); // ### TODO: エラー処理
	cur->next = list;
	return (command);
}

t_command	*parse(t_token_list *token)
{
	t_command *command;

	command = new_command(CM_SIMPLE);
	if (!command) //### TODO: エラー処理考える
		return (NULL);
	while (token && token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
			append_command_words(command, token->word);
		token = token->next;
	}
}