/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:38:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/12 18:11:54 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fatal_error(char *func, char *str)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", func, str);
}

void parser_error(char *str)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", str);
}

void parser_operator_error(const char *msg, const char *detail)
{
	if (!detail)
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", msg);
	else
		ft_dprintf(STDERR_FILENO, "minishell: %s '%s'\n", msg, detail);
}

void internal_error(const char *msg, const char *detail)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s '%s'\n", msg, detail);
}

void	sys_error(char *err_txt)
{
	int	e;

	e = errno;
	ft_dprintf(STDERR_FILENO, "minishell: %s", err_txt);
	ft_dprintf(STDERR_FILENO, ": %s\n", strerror(e));
}

void builtin_error(char *func, char *arg, char *msg)
{
	if (!arg)
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", func, msg);
	else
		ft_dprintf(STDERR_FILENO, "minishell: %s: '%s': %s\n", func, arg, msg);
}
