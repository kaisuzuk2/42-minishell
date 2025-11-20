/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:09:53 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/04/26 20:33:37 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	size;
	char	*res;

	slen = ft_strlen(s);
	if (start >= slen)
	{
		res = (char *)ft_calloc(1, sizeof(char));
		if (res == NULL)
			return (NULL);
	}
	else
	{
		if (slen - start > len)
			size = len;
		else
			size = slen - start;
		size += 1;
		res = (char *)malloc(sizeof(char) * size);
		if (res == NULL)
			return (NULL);
		ft_strlcpy(res, (s + start), size);
	}
	return (res);
}
