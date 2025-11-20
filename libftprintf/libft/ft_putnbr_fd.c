/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:44:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/25 18:38:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_fd(int n, int fd)
{
	char	res[12];
	int		i;
	long	ln;

	ln = n;
	i = 11;
	if (ln < 0)
		ln *= -1;
	res[i] = '\0';
	while (ln)
	{
		res[--i] = (ln % 10) + '0';
		ln /= 10;
	}
	if (n < 0)
		res[--i] = '-';
	return (ft_putstr_fd(&res[i], fd));
}
