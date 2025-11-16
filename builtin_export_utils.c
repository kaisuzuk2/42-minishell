/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:40:03 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 17:45:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	map_swap(t_shell_var_map *m1, t_shell_var_map *m2)
{
	t_shell_var_map	tmp;

	tmp = *m1;
	*m1 = *m2;
	*m2 = tmp;
}

void	sort_var_arr(t_shell_var_map *env, size_t size)
{
	int	i;
	int	j;

	i = 0;
	if (size <= 0)
		return ;
	while (i < size)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(env[j].name, env[j + 1].name) > 0)
				map_swap(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

void	free_env_map(t_shell_var_map *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		free(env[i].name);
		free(env[i].value);
		i++;
	}
	free(env);
}

void	print_var_map(t_shell_var_map *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s", env[i].name);
		if (env[i].value)
			ft_dprintf(STDOUT_FILENO, "=\"%s\"", env[i].value);
		ft_dprintf(STDOUT_FILENO, "\n");
		i++;
	}
}

t_shell_var_map	*make_shell_env_map(t_shell_var_map *var_arr, t_varlist *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!is_exported(env->var))
		{
			env = env->next;
			continue ;
		}
		var_arr[i].name = savestring(env->var->name);
		if (!var_arr[i].name)
			return (free_env_map(var_arr), NULL);
		if (!env->var->value)
			var_arr[i].value = NULL;
		else
		{
			var_arr[i].value = savestring(env->var->value);
			if (!var_arr[i].value)
				return (free_env_map(var_arr), NULL);
		}
		env = env->next;
		i++;
	}
	return (var_arr);
}
