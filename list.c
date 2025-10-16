/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:56:34 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/16 09:57:47 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t list_length(t_generic_list *list)
{
	size_t res;

	res = 0;
	while (list)
	{
		list = list->next;
		res++;
	}
	return (res);
}