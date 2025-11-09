/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_tokenkinds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:35:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/26 09:09:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize_utils.c
t_bool	startswith(const char *s, const char *op);

t_bool	is_shellbrank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*is_metacharacter(char c)
{
	return (ft_strchr("&|;<>()", c));
}

t_bool	is_word(char *line)
{
	return (*line && !is_metacharacter(*line));
}

t_bool	is_operator(char *line)
{
	int			i;
	const char	*operators[] = {"&&", "&", "||", "|", ";;", ";", "<>", "<<-",
			"<<", "<&", "<", ">|", ">>", ">&", ">", "(", ")"};

	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!startswith(line, operators[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_quote(char c)
{
	return (c == SINGLE_QUOTE_CHAR || c == DOUBLE_QUOTE_CHAR);
}
