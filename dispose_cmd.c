/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:59:46 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 15:33:26 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dispose_desc_words(t_word_list *list);

void	dispose_redirects(t_redirect *list)
{
	t_redirect	*t;

	while (list)
	{
		t = list;
		list = list->next;
		dispose_word(t->redirectee.filename);
		free(t->here_doc_eof);
		free(t);
	}
}

void	dispose_simple_command(t_command *command)
{
	if (!command)
		return ;
	if (command->redirects)
		dispose_redirects(command->redirects);
	dispose_desc_words(command->words);
	free(command);
}

void	dispose_command(t_command *command)
{
	t_command	*simple;
	t_command	*t;

	if (!command)
		return ;
	while (command)
	{
		t = command;
		command = command->next;
		simple = t->command;
		dispose_simple_command(simple);
		free(t);
	}
}
