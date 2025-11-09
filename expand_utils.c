/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:28:03 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/02 10:55:28 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	wait_for(pid_t lastpid);

t_bool	is_hasdollar(t_word_desc *desc)
{
	return (desc->flag == W_HASDOLLAR);
}

t_bool is_d_quote(t_word_desc *desc)
{
	return (desc->flag == W_DQUOTE);
}

t_bool is_s_quote(t_word_desc *desc)
{
	return (desc->flag == W_SQUOTE);
}

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