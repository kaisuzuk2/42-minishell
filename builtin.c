/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:08 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/20 09:03:31 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_func *find_shell_builtin(const char *name)
{
	const char *builtin_name[] = {"echo", "env", "export"};
	const t_builtin_func *builtin_table[] = {&builtin_echo, &builtin_env, &builtin_export};
	int i;

	i = 0;
	while (i < sizeof(builtin_name) / sizeof(*builtin_name))
	{
		if (!ft_strcmp(name, builtin_name[i]))
			return (builtin_table[i]);
		i++;
	}
	return (NULL);
}