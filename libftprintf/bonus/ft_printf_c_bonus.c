/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:53:12 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/06/01 00:50:36 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_printout_c(const unsigned char uc, t_flg *flg)
{
	int	res;

	res = 0;
	if (flg->ladjust)
	{
		if (write(1, &uc, 1) == -1)
			return (-1);
		res++;
	}
	while (flg->field_width && --flg->field_width)
	{
		if (ft_putchar(' ') == -1)
			return (-1);
		res++;
	}
	if (!flg->ladjust)
	{
		if (write(1, &uc, 1) == -1)
			return (-1);
		res++;
	}
	return (res);
}

int	ft_printf_c(int c, t_flg *flg)
{
	int					res;
	const unsigned char	uc = (const unsigned char)c;

	res = ft_printout_c(uc, flg);
	return (res);
}
