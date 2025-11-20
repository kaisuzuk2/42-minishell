/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:27:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 16:36:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_putnstr(const char *str, int size)
{
	int	res;

	res = 0;
	while (size--)
	{
		if (ft_putchar(*str) == -1)
			return (-1);
		str++;
		res++;
	}
	return (res);
}

static int	ft_printout_s(const char *str, t_flg *flg, t_utils *utl)
{
	if (!flg->ladjust && ft_putnchar(' ', utl->field_pad) == -1)
		return (-1);
	ft_putnstr(str, utl->act_len);
	if (flg->ladjust && ft_putnchar(' ', utl->field_pad) == -1)
		return (-1);
	return (utl->total_len);
}

int	ft_printf_s(const char *str, t_flg *flg)
{
	t_utils	*utl;
	int		res;

	utl = (t_utils *)malloc(sizeof(t_utils));
	if (!utl)
		return (-1);
	if (!str)
		str = SERROR;
	if (flg->sharp)
		flg->sharp = FALSE;
	ft_printf_set_utils(str, flg, utl);
	res = ft_printout_s(str, flg, utl);
	free(utl);
	return (res);
}
