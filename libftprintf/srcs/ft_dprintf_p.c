/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:46:24 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/05 20:17:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printaddr(int fd, uintptr_t np)
{
	int	count;

	count = 0;
	if (np >= 16)
		count = ft_printaddr(fd, np / 16);
	count += ft_putchar_fd("0123456789abcdef"[np % 16], fd);
	return (count);
}

int	ft_dprintf_p(int fd, void *p)
{
	int	res;

	if (p == NULL)
		return (write(fd, "(nil)", 5));
	res = 0;
	res += ft_putstr_fd("0x", fd);
	return (res + ft_printaddr(fd, (uintptr_t)p));
}
