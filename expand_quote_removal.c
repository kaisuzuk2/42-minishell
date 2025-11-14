/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:49:10 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/14 14:34:49 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*string_quote_removal(char *string, char quote)
{
	char	set[2];

	set[0] = quote;
	set[1] = '\0';
	return (ft_strtrim(string, set));
}

char	*expand_quote(char **document_p, char *document)
{
	char	quote;
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	quote = document[i++];
	while (document[i] != quote)
		i++;
	tmp = ft_substr(document, 0, i);
	if (!tmp)
		return (NULL);
	res = string_quote_removal(tmp, quote);
	if (!res)
		return (free(tmp), NULL);
	free(tmp);
	*document_p = &document[i + 1];
	return (res);
}

char	*quote_removal_delimiter(char *delimiter)
{
	char	*new;
	char	*q;
	char	*p;
	char	quote;

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
