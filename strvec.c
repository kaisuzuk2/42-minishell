/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:35:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 17:20:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO 複製する必要あるかね
char	**strvec_from_word_list(t_word_list *list)
{
	const size_t	count = list_length((t_generic_list *)list);
	char			**arr;
	size_t			i;

	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count)
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
