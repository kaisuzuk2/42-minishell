/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:56:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 17:08:21 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int un)
{
	char	buf[11];
	int		i;

	i = 10;
	buf[i] = '\0';
	while (1)
	{
		buf[--i] = un % 10 + '0';
		un /= 10;
		if (!un)
			break ;
	}
	return (ft_strdup(&buf[i]));
}
