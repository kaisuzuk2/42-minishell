/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:31:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 15:22:10 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	set_variable_name(t_shell_var *map, char *env)
{
	char	*name_ptr;
	int		i;

	i = 0;
	name_ptr = ft_strchr(env, '=');
	if (!name_ptr)
		map->name = savestring(env);
	else
	{
		while (env[i])
		{
			if (env[i] == '=')
				break ;
			i++;
		}
		map->name = savestring(env);
		map->name[i] = '\0';
	}
	if (!map->name)
		return (FALSE);
	return (TRUE);
}

t_bool	set_variable_value(t_shell_var *map, char *env)
{
	char	*value_ptr;

	value_ptr = ft_strchr(env, '=');
	if (!value_ptr)
		return (TRUE);
	value_ptr++;
	if (!*value_ptr)
	{
		map->value = NULL;
		return (TRUE);
	}
	map->value = savestring(value_ptr);
	if (!map->value)
		return (FALSE);
	return (TRUE);
}

t_bool	set_variable_exportstr(t_shell_var *map, char *env)
{
	map->exportstr = savestring(env);
	if (!map->exportstr)
		return (FALSE);
	return (TRUE);
}

void	set_variable_attributes(t_shell_var *map, int flag)
{
	map->attributes = flag;
}
