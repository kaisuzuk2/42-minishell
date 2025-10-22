/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:38:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/22 16:13:52 by kaisuzuk         ###   ########.fr       */
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