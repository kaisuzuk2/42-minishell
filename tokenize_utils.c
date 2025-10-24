/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:39:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/24 17:36:30 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize_utils_tokenkinds.c
t_bool	is_shellbrank(char c);

void	skip_shellbrank(char **line)
{
	while (**line && is_shellbrank(**line))
		(*line)++;
}

void	set_token_flg(char *line, t_word_desc *desc)
{
	if (ft_strchr(line, '$'))
		desc->flag = W_HASDOLLAR;
	if (*line == '\'')
		desc->flag = W_SQUOTE;
	else if (*line == '\"')
		desc->flag = W_DQUOTE;
}

t_bool	startswith(const char *s, const char *op)
{
	return (ft_strncmp(s, op, ft_strlen(op)));
}