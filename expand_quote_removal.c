/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:49:10 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/10 13:58:25 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_quote_removal(char *string, char quote)
{
	char	set[2];

	set[0] = quote;
	set[1] = '\0';
	return (ft_strtrim(string, set));
}

char *quote_removal_delimiter(char *delimiter)
{
	char *new;
	char *q;
	char *p;
	char quote;

	new = (char *)xmalloc(sizeof(char) * (ft_strlen(delimiter) + 1));
	if (!new)
		return (NULL);
	p = delimiter;
	q = new;
	quote = 0;
	while (*p)
	{
		if (!quote && (*p == SINGLE_QUOTE_CHAR || *p == DOUBLE_QUOTE_CHAR))
			quote = *p++;
		else if (quote && *p == quote)
		{
			p++;
			quote = 0;
		}
		else
			*q++ = *p++;
	}
	*q = '\0';
	return (new);
}