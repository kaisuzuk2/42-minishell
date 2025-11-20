/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:58:00 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 16:36:58 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_printf_init_utils(t_utils *utl)
{
	utl->act_len = 0;
	utl->field_pad = 0;
	utl->prec_pad = 0;
	utl->total_len = 0;
}

static void	ft_printf_set_string_utils(t_flg *flg, t_utils *utl, size_t len)
{
	if (flg->prec)
	{
		if (flg->prec_width < len)
			utl->act_len = flg->prec_width;
		else
			utl->act_len = len;
	}
	else
		utl->act_len = len;
}

void	ft_printf_set_utils(const char *strn, t_flg *flg, t_utils *utl)
{
	size_t	len;

	len = ft_strlen(strn);
	ft_printf_init_utils(utl);
	if (flg->prec)
	{
		if (!flg->is_string && flg->prec_width > len)
			utl->prec_pad = flg->prec_width - len;
		else if (flg->is_string && flg->prec_width < len)
			utl->prec_pad = flg->prec_width;
		else if (flg->is_string && flg->prec_width > len)
			utl->prec_pad = len;
	}
	if (flg->sharp)
		utl->act_len = SHARP_SIZE;
	if (!flg->sign)
		utl->act_len += len + utl->prec_pad;
	else
		utl->act_len += len + utl->prec_pad + SIGN_SIZE;
	if (flg->is_string)
		ft_printf_set_string_utils(flg, utl, len);
	if (flg->field_width > utl->act_len)
		utl->field_pad = flg->field_width - utl->act_len;
	utl->total_len = utl->act_len + utl->field_pad;
}
