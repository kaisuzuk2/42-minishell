/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:55:43 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/06/01 00:45:03 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_printf_format(const char **fmt, va_list ap, t_flg *flg)
{
	(*fmt)++;
	ft_printf_set_flg_prec(fmt, flg);
	if (**fmt == 'c')
		return (ft_printf_c(va_arg(ap, int), flg));
	else if (**fmt == 's')
		return (ft_printf_s(va_arg(ap, char *), flg));
	else if (**fmt == 'd' || **fmt == 'i')
		return (ft_printf_di(va_arg(ap, int), flg));
	else if (**fmt == 'u')
		return (ft_printf_u(va_arg(ap, unsigned int), flg));
	else if (**fmt == 'p')
		return (ft_printf_p(va_arg(ap, void *), flg));
	else if (**fmt == 'x')
		return (ft_printf_x(va_arg(ap, unsigned int), flg, 0));
	else if (**fmt == 'X')
		return (ft_printf_x(va_arg(ap, unsigned int), flg, 16));
	else
		return (ft_putchar(**fmt));
}

static int	ft_vprintf(const char *format, va_list ap)
{
	t_flg	*flg;
	int		res;
	int		tmp;

	flg = (t_flg *)malloc(sizeof(t_flg));
	if (!flg)
		return (-1);
	res = 0;
	while (*format)
	{
		if (*format != '%')
		{
			if (ft_putchar(*format) == -1)
				return (-1);
			res++;
			format++;
			continue ;
		}
		tmp = ft_printf_format(&format, ap, flg);
		if (tmp == -1)
			return (-1);
		res += tmp;
		format++;
	}
	return (free(flg), res);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		res;

	if (format == NULL)
		return (-1);
	if (ft_strchr(format, '%') == NULL)
		return (ft_putstr(format));
	va_start(args, format);
	res = ft_vprintf(format, args);
	va_end(args);
	return (res);
}
