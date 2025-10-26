/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:50:16 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/26 10:18:19 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *xmalloc(size_t size)
{
	void *tmp;

	tmp = malloc(size);
	if (!tmp)
	{
		fatal_error("malloc", MALLOC_ERR_STR);
		return (NULL);
	}
	return (tmp);
}

void *xcalloc(size_t nmemb, size_t size)
{
	void *tmp;

	tmp = ft_calloc(nmemb, size);
	if (!tmp)
	{
		fatal_error("ft_calloc", MALLOC_ERR_STR);
		return (NULL);
	}
	return (tmp);
}