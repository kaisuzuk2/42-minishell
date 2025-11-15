/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:32:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 15:33:10 by kaisuzuk         ###   ########.fr       */
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

	if (!list)
		return ;
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