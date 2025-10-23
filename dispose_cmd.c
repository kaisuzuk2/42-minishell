/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:59:46 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/23 15:15:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dispose_word(t_word_desc *w)
{
	if (!w)
		return ;
	free(w->word);
	free(w);
}

void	dispose_token_words(t_token_list *list)
{
	t_token_list	*t;

	while (list)
	{
		t = list;
		list = list->next;
		dispose_word(t->word);
		free(t);
	}
}

void	dispose_desc_words(t_word_list *list)
{
	t_word_list	*t;

	while (list)
	{
		t = list;
		list = list->next;
		dispose_word(t->word);
		free(t);
	}
}

void	dispose_redirects(t_redirect *list)
{
	t_redirect	*t;

	while (list)
	{
		t = list;
		dispose_word(t->redirectee.filename);
		free(t->here_doc_eof);
		free(t);
		list = list->next;
	}
}

void dispose_simple_command(t_command *command)
{
	if (command->redirects)
		dispose_redirects(command->redirects);
	dispose_desc_words(command->words);
	free(command);
}

void	dispose_command(t_command *command)
{
	t_command *simple;
	t_command *t;

	while (command)
	{
		if (!command)
			return ;
		t = command;
		command = command->next;
		simple = t->command;
		if (t->redirects)
			dispose_redirects(t->redirects);
		if (simple && simple->redirects)
			dispose_redirects(simple->redirects);
		if (t->words)
			dispose_desc_words(t->words);
		if (simple && simple->words)
			dispose_desc_words(simple->words);
		free(simple);
		free(t);
	}
}