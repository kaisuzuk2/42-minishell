/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:44:40 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 16:38:00 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putnchar(int c, int size)
{
	int	res;

	res = 0;
	while (size--)
	{
		if (ft_putchar(c) == -1)
			return (-1);
		res++;
	}
	return (res);
}
