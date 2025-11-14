/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ifs_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:15:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/14 14:34:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_ifs(char c)
{
	const char	*ifs = " \t\n";

	return (ft_strchr(ifs, c) != 0);
}

static size_t	ft_word_count(char const *s)
{
	size_t	res;
	int		flg;

	res = 0;
	flg = 1;
	while (*s)
	{
		if (flg && !is_ifs(*s))
		{
			flg = 0;
			res++;
		}
		else if (is_ifs(*s))
			flg = 1;
		s++;
	}
	return (res);
}

static char	*ft_extract_word(const char *p, int len)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, p, len + 1);
	if (!res)
		return (NULL);
	return (res);
}

static char	*ft_fill_word(char const **p)
{
	size_t	str_len;
	char	*res;
	char	quate;

	str_len = 0;
	quate = 0;
	while (is_ifs(**p))
		(*p)++;
	while ((*p)[str_len])
	{
		if (is_ifs((*p)[str_len]))
			break ;
		str_len++;
	}
	res = ft_extract_word(*p, str_len);
	*p = *p + str_len;
	return (res);
}

char	**ifs_split(char const *s)
{
	char	**head;
	char	**tmp;
	size_t	head_size;

	head_size = ft_word_count(s);
	head = (char **)malloc(sizeof(char *) * (head_size + 1));
	if (head == NULL)
		return (NULL);
	tmp = head;
	while (tmp < &head[head_size])
	{
		*tmp = ft_fill_word(&s);
		if (!*tmp)
			return (dispose_char_arr(head), NULL);
		tmp++;
	}
	*tmp = NULL;
	return (head);
}
