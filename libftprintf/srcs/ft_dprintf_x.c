/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:57:42 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/05 20:18:03 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dprintf_x(int fd, unsigned int un, unsigned int capital)
{
	char	buf[9];
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
	return (ft_putstr_fd(&buf[i], fd));
}
