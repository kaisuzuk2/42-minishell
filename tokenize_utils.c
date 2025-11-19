/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:39:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 12:18:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_shellblank(char **line)
{
	while (**line && is_shellblank(**line))
		(*line)++;
}

void	set_token_flg(char *line, t_word_desc *desc)
{
	desc->flag = 0;
	if (ft_strchr(line, SINGLE_QUOTE_CHAR))
		desc->flag |= W_SQUOTE;
	if (ft_strchr(line, DOUBLE_QUOTE_CHAR))
		desc->flag |= W_DQUOTE;
	if (ft_strchr(line, DOLLAR_CHAR))
		desc->flag |= W_HASDOLLAR;
}

t_bool	is_match_op(char *str, size_t len, const char *op)
{
	return (len == ft_strlen(op) && !ft_strncmp(str, op, len));
}
