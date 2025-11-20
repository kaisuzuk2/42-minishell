/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:49:05 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 16:37:10 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static const char	*ft_unsinged_int_to_char(unsigned int un, char *buf)
{
	int	i;

	i = 10;
	buf[--i] = '\0';
	while (1)
	{
		buf[--i] = un % 10 + '0';
		un /= 10;
		if (!un)
			break ;
	}
	return (&buf[i]);
}

static int	ft_printout_u(const char *strn, t_flg *flg, t_utils *utl)
{
	if (flg->padc == '0' && flg->sign && ft_putchar(flg->sign) == -1)
		return (-1);
	if (!flg->ladjust && utl->field_pad && ft_putnchar(flg->padc,
			utl->field_pad) == -1)
		return (-1);
	if (flg->padc != '0' && flg->sign && ft_putchar(flg->sign) == -1)
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

int	ft_printf_u(unsigned int un, t_flg *flg)
{
	const char	*strn;
	t_utils		*utl;
	int			res;
	char		buf[11];

	utl = (t_utils *)malloc(sizeof(t_utils));
	if (!utl)
		return (-1);
	strn = ft_unsinged_int_to_char(un, buf);
	if (flg->sharp)
		flg->sharp = FALSE;
	ft_printf_set_utils(strn, flg, utl);
	if (flg->prec && flg->prec_width == 0 && un == 0)
		strn = "";
	res = ft_printout_u(strn, flg, utl);
	free(utl);
	return (res);
}
