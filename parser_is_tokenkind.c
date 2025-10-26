/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_is_tokenkind.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 09:43:21 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/26 09:44:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_redirect(t_token_kind kind)
{
	return (kind == TK_GREAT_GREAT || kind == TK_GREAT || kind == TK_LESS_LESS
		|| kind == TK_LESS);
}

t_bool is_wordtoken(t_token_kind kind)
{
	return (kind == TK_WORD);
}

t_bool is_eoftoken(t_token_kind kind)
{
	return (kind == TK_EOF);
}

t_bool is_pipetoken(t_token_kind kind)
{
	return (kind == TK_PIPE);
}