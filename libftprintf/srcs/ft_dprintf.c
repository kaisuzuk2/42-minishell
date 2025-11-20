/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:10:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/25 18:38:25 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_dprintf_format(int fd, va_list args, const char *fmt)
{
	if (*fmt == 'c')
		return (ft_dprintf_c(fd, va_arg(args, int)));
	else if (*fmt == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (*fmt == 'p')
		return (ft_dprintf_p(fd, va_arg(args, void *)));
	else if (*fmt == 'd' || *fmt == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (*fmt == 'u')
		return (ft_dprintf_u(fd, va_arg(args, unsigned int)));
	else if (*fmt == 'x')
		return (ft_dprintf_x(fd, va_arg(args, unsigned int), 0));
	else if (*fmt == 'X')
		return (ft_dprintf_x(fd, va_arg(args, unsigned int), 16));
	else
		return (ft_putchar_fd(*fmt, fd));
}

static int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	int	res;
	int	tmp;

	res = 0;
	if (ft_strchr(format, '%') == NULL)
		return (ft_putstr(format));
	while (*format)
	{
		if (*format != '%')
		{
			if (ft_putchar_fd(*format, fd) == -1)
				return (-1);
			res++;
			format++;
			continue ;
		}
		++format;
		tmp = ft_dprintf_format(fd, ap, format);
		if (tmp == -1)
			return (-1);
		res += tmp;
		++format;
	}
	return (res);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		res;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	res = ft_vdprintf(fd, format, args);
	va_end(args);
	return (res);
}
