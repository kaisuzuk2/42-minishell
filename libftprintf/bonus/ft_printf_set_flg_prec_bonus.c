/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_flg_prec_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:00:53 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 15:15:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_printf_init_flg(t_flg *flg)
{
	flg->ladjust = FALSE;
	flg->prec = FALSE;
	flg->prec_width = 0;
	flg->sharp = FALSE;
	flg->sign = 0;
	flg->field_width = 0;
	flg->prec_width = 0;
	flg->padc = ' ';
	flg->is_string = FALSE;
	flg->sharp_ox = "0x";
}

static void	ft_printf_set_prec(const char **fmt, t_flg *flg)
{
	if (**fmt != '.')
		return ;
	flg->prec = TRUE;
	(*fmt)++;
	while (ft_isdigit(**fmt))
	{
		flg->prec_width = (flg->prec_width * 10) + (**fmt - '0');
		(*fmt)++;
	}
}

static void	ft_printf_set_flg(const char **fmt, t_flg *flg)
{
	while (1)
	{
		if (**fmt == '-')
			flg->ladjust = TRUE;
		else if (!flg->ladjust && **fmt == '0')
			flg->padc = '0';
		else if (**fmt == '#')
			flg->sharp = TRUE;
		else if (**fmt == '+')
			flg->sign = '+';
		else if (!flg->sign && **fmt == ' ')
			flg->sign = ' ';
		else
			break ;
		(*fmt)++;
	}
	while (ft_isdigit(**fmt))
	{
		flg->field_width = (flg->field_width * 10) + (**fmt - '0');
		(*fmt)++;
	}
}

void	ft_printf_set_flg_prec(const char **fmt, t_flg *flg)
{
	ft_printf_init_flg(flg);
	ft_printf_set_flg(fmt, flg);
	ft_printf_set_prec(fmt, flg);
	if (**fmt == 's')
		flg->is_string = TRUE;
	else if (**fmt == 'p')
		flg->sharp = TRUE;
}
