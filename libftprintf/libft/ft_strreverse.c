/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:09:47 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/04/30 11:59:46 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(char *s1, char *s2)
{
	char	tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	*ft_strreverse(char *str)
{
	size_t	len;
	size_t	size;
	size_t	i;

	len = ft_strlen(str);
	size = len / 2;
	i = 0;
	while (i < size)
	{
		ft_swap(&str[i], &str[len - 1 - i]);
		i++;
	}
	return (str);
}
