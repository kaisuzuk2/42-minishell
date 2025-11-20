/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:05:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/05 19:26:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int			res;
	int			i;
	char		buf[12];
	long int	un;

	res = 0;
	i = 11;
	un = n;
	if (un < 0)
		un *= -1;
	buf[i] = '\0';
	while (1)
	{
		buf[--i] = un % 10 + '0';
		un /= 10;
		res++;
		if (!un)
			break ;
	}
	if (n < 0)
		buf[--i] = '-';
	ft_putstr(&buf[i]);
	return (11 - i);
}
