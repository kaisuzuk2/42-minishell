/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:16:44 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 16:35:53 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*ft_to_hex(uintptr_t up, char *buf)
{
	size_t	i;

	i = 18;
	buf[i] = '\0';
	while (1)
	{
		buf[--i] = "0123456789abcdef"[up % 16];
		up /= 16;
		if (!up)
			break ;
	}
	return (&buf[i]);
}

static int	ft_printout_p(const char *strn, t_flg *flg, t_utils *utl)
{
	if (flg->padc == '0' && ft_putstr(flg->sharp_ox) == -1)
		return (-1);
	if (!flg->ladjust && utl->field_pad && ft_putnchar(flg->padc,
			utl->field_pad) == -1)
		return (-1);
	if (flg->padc != '0' && ft_putstr(flg->sharp_ox) == -1)
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

int	ft_printf_p(void *p, t_flg *flg)
{
	uintptr_t	pn;
	t_utils		*utl;
	char		buf[19];
	const char	*strn;
	int			res;

	pn = (uintptr_t)p;
	utl = (t_utils *)malloc(sizeof(t_utils));
	if (!utl)
		return (-1);
	strn = ft_to_hex(pn, buf);
	if (!p)
	{
		strn = PERROR;
		flg->sharp_ox = "";
		flg->sharp = FALSE;
	}
	ft_printf_set_utils(strn, flg, utl);
	res = ft_printout_p(strn, flg, utl);
	free(utl);
	return (res);
}
