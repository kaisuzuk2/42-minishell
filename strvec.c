/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:35:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 11:40:34 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strvec_from_word_list(t_word_list *list)
{
	char	**arr;
	size_t	i;

	arr = (char **)malloc(sizeof(char *) * (list_length((t_generic_list *)list)
				+ 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (list)
	{
		arr[i] = savestring(list->word->word);
		if (!arr[i])
			return (dispose_char_arr(arr), NULL);
		list = list->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
