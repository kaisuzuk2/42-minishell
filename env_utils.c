/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:27:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 12:22:31 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_env_arr(t_varlist *env)
{
	const size_t len = list_length((t_generic_list *)env);
	char **res;
	int i;

	res = (char **)xmalloc(sizeof(char *) * len);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		res[i] = savestring(env->var->exportstr);
		if (!res[i])
		{
			while (i >= 0)
			{
				free(res[i]);
				i--;
			}
			return (NULL);
		}
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

t_shell_var *list_getshell_var(t_varlist *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->var->name, key))
			return (env->var);
		env = env->next;
	}
	return (NULL);
}

// ### TODO: フラグチェック
char *list_getenv(t_varlist *env, char *key)
{
	if (!key)
		return (NULL);
	if (*key == 0)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->var->name, key)) // ### TODO: strcmpでいいか確認
			return (env->var->value);
		env = env->next;
	}
	return (NULL);
}

static t_bool add_variable_item(t_varlist *env, char *exportstr)
{
	while (env->next)
		env = env->next;
	env->next = create_varlist();
	if (!env->next)
		return (FALSE);
	env = env->next;
	env->var = create_shell_var();
	if (!env->var)
		return (FALSE);
	if (!set_variable_name(env->var, exportstr))
		return (FALSE);
	if (!set_variable_value(env->var, exportstr))
		return (FALSE);
	if (!set_variable_exportstr(env->var, exportstr))
		return (FALSE);
	set_variable_attributes(env->var);	
	return (TRUE);
}

t_bool update_variable_item(t_varlist *env, char *exportstr)
{
	char *key;
	t_shell_var *target;

	key = get_env_key(exportstr);
	if (!key)
		return (FALSE);
	target = list_getshell_var(env, key);
	if (!target)
		return (free(key), add_variable_item(env, exportstr));
	free(key);
	free(target->value);
	free(target->exportstr);
	set_variable_attributes(target);
	if (!set_variable_exportstr(target, exportstr))
		return (FALSE);
	if (!set_variable_value(target, exportstr))
		return (FALSE);
	return (TRUE);
}