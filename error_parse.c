/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:31:16 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 13:31:33 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_error(char *str)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", str);
}

void	parser_operator_error(const char *msg, const char *detail)
{
	if (!detail)
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", msg);
	else
		ft_dprintf(STDERR_FILENO, "minishell: %s '%s'\n", msg, detail);
}
