/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:43:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 10:21:32 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_status(t_shell_env *env)
{
	return (env->last_status);
}

char	*get_current_working_directory(t_shell_env *shell_env)
{
	return (shell_env->tcwd);
}

char	**get_env_arr(t_varlist *env)
{
	const size_t	len = list_length((t_generic_list *)env);
	char			**res;
	int				i;

	res = (char **)xmalloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (env)
	{
		if (!is_exported(env->var))
		{
			env = env->next;
			continue ;
		}
		res[i] = savestring(env->var->exportstr);
		if (!res[i])
			return (dispose_char_arr(res), NULL);
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*get_listenv(t_varlist *env, char *key)
{
	if (!key)
		return (NULL);
	if (*key == 0)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->var->name, key))
			return (env->var->value);
		env = env->next;
	}
	return (NULL);
}

t_shell_var	*get_shell_var(t_varlist *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->var->name, key))
			return (env->var);
		env = env->next;
	}
	return (NULL);
}
