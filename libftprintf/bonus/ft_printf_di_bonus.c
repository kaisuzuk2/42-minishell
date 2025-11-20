/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:39 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 16:35:36 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static const char	*ft_int_to_char(int n, char *buf)
{
	int		i;
	long	ln;

	i = 11;
	ln = (long)n;
	if (ln < 0)
		ln *= -1;
	buf[i] = '\0';
	while (1)
	{
		buf[--i] = ln % 10 + '0';
		ln /= 10;
		if (!ln)
			break ;
	}
	return (&buf[i]);
}

int	ft_printout_di(const char *strn, t_flg *flg, t_utils *utl)
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

int	ft_printf_di(int n, t_flg *flg)
{
	t_utils		*utl;
	char		buf[12];
	const char	*strn;
	int			res;

	utl = (t_utils *)malloc(sizeof(t_utils));
	if (!utl)
		return (-1);
	strn = ft_int_to_char(n, buf);
	if (n < 0)
		flg->sign = '-';
	if (flg->sharp)
		flg->sharp = FALSE;
	ft_printf_set_utils(strn, flg, utl);
	if (flg->prec && flg->prec_width == 0 && n == 0)
		strn = "";
	res = ft_printout_di(strn, flg, utl);
	free(utl);
	return (res);
}
