/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:06:41 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 17:04:50 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*ft_to_hex(unsigned int un, char *buf, int capital)
{
	size_t	i;

	i = 8;
	buf[i] = '\0';
	while (1)
	{
		buf[--i] = "0123456789abcdef0123456789ABCDEF"[un % 16 + capital];
		un /= 16;
		if (!un)
			break ;
	}
	return (&buf[i]);
}

static int	ft_printout_x(const char *strn, t_flg *flg, t_utils *utl)
{
	if (flg->sharp && flg->padc == '0' && ft_putstr(flg->sharp_ox) == -1)
		return (-1);
	if (!flg->ladjust && utl->field_pad && ft_putnchar(flg->padc,
			utl->field_pad) == -1)
		return (-1);
	if (flg->sharp && flg->padc != '0' && ft_putstr(flg->sharp_ox) == -1)
		return (-1);
	if (utl->prec_pad && ft_putnchar('0', utl->prec_pad) == -1)
		return (-1);
	if (ft_putstr(strn) == -1)
		return (-1);
	if (flg->ladjust && utl->field_pad && ft_putnchar(flg->padc,
			utl->field_pad) == -1)
		return (-1);
	return (utl->total_len);
}

int	ft_printf_x(unsigned int un, t_flg *flg, int capital)
{
	t_utils		*utl;
	char		buf[9];
	const char	*strn;
	int			res;

	utl = (t_utils *)malloc(sizeof(t_utils));
	if (!utl)
		return (-1);
	if (capital == 16)
		flg->sharp_ox = "0X";
	if (un == 0)
	{
		flg->sharp_ox = "";
		flg->sharp = FALSE;
	}
	strn = ft_to_hex(un, buf, capital);
	if (flg->prec && flg->prec_width == 0 && un == 0)
		strn = "";
	ft_printf_set_utils(strn, flg, utl);
	res = ft_printout_x(strn, flg, utl);
	free(utl);
	return (res);
}
