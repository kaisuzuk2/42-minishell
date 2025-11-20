/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:10:01 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/05 20:17:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dprintf_u(int fd, unsigned int un)
{
	char	buf[11];
	int		i;

	i = 10;
	buf[i] = '\0';
	while (1)
	{
		buf[--i] = "0123456789"[un % 10];
		un /= 10;
		if (!un)
			break ;
	}
	return (ft_putstr_fd(&buf[i], fd));
}
