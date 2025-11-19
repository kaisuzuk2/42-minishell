/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_tokenkinds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:35:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 09:04:19 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_shellblank(char c)
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

t_bool	is_quote(char c)
{
	return (c == SINGLE_QUOTE_CHAR || c == DOUBLE_QUOTE_CHAR);
}
