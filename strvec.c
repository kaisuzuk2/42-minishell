/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:35:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/16 10:07:23 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_command -> char **
// ### TODO:  allocで複製するかどうかを判定している。必要か考える
// char **strvec_from_word_list (WORD_LIST *list, int alloc, int starting_index, int *ip)
char	**strvec_from_word_list(t_word_list *list)
{
	size_t count;
	char **arr;
	size_t i;

	count = list_length((t_generic_list *)list);
	arr = (char **)malloc(sizeof(char *) * (count + startin_index + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		arr[i] = list;
		list = list->next;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}