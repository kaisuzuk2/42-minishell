/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:48:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/03 00:48:39 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char		buf[12];
	int			i;
	long int	un;

	i = 11;
	buf[i] = '\0';
	un = n;
	if (un < 0)
		un *= -1;
	while (1)
	{
		buf[--i] = un % 10 + '0';
		un /= 10;
		if (!un)
			break ;
	}
	if (n < 0)
		buf[--i] = '-';
	return (ft_strdup(&buf[i]));
}
