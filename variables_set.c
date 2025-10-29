/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:31:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 11:52:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_key(char *env)
{
	char *res;
	int i;

	if (!ft_strchr(env, '='))
		return (savestring(env));
	res = savestring(env);
	if (!res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		if (res[i] == '=')
			break;
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_bool	set_variable_name(t_shell_var *map, char *env)
{
	char	*name_ptr;
	int i;

	i = 0;
	name_ptr = ft_strchr(env, '='); // ### TODO: マクロ化
	if (!name_ptr)
		map->name = savestring(env);
	else
	{
		while (env[i])
		{
			if (env[i] == '=')
				break;
			i++;
		}
		map->name = savestring(env);
		map->name[i] = '\0';
	}
	if (!map->name)
		return (FALSE);
	return (TRUE);
}

// ### TODO: nameを先に設定するとvalueが設定できなくなる
t_bool	set_variable_value(t_shell_var *map, char *env)
{
	char	*value_ptr;

	value_ptr = ft_strchr(env, '=');
	if (!value_ptr)
		return (TRUE);
	value_ptr++;
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

void set_variable_attributes(t_shell_var *map)
{
	map->attributes = 1;
}