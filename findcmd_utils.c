/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:31:16 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 10:13:30 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_absolute_program(char *arg)
{
	return (ft_strchr(arg, '/') != NULL);
}

char	*savestring(char *str)
{
	char	*res;

	res = ft_strdup(str);
	if (!res)
		return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	return (res);
}
