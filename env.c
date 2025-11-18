/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:27:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 11:51:06 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_exported(t_shell_var *env_var)
{
	if (!env_var)
		return (FALSE);
	return (env_var->attributes == TRUE);
}

static t_bool	add_variable_item(t_varlist *env, char *exportstr, int flag)
{
	t_varlist *cur;

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
	set_variable_attributes(env->var, flag);
	return (TRUE);
}

// static t_bool	add_variable_item(t_varlist *env, char *exportstr, int flag)
// {
// 	t_varlist	*cur;

// 	if (!env)
// 	{
// 		cur = env;
// 		cur = create_varlist();
// 	}
// 	else
// 	{
// 		cur = env;
// 		while (cur->next)
// 			cur = cur->next;
// 		cur->next =	create_varlist();
// 		cur = cur->next;
// 	}
// 	if (!cur)
// 		return (FALSE);
// 	cur->var = create_shell_var();
// 	if (!cur->var)
// 		return (free(cur), FALSE);
// 	if (!set_variable_name(cur->var, exportstr))
// 		return (FALSE);
// 	if (!set_variable_value(cur->var, exportstr))
// 		return (FALSE);
// 	if (!set_variable_exportstr(cur->var, exportstr))
// 		return (FALSE);
// 	set_variable_attributes(cur->var, flag);
// 	return (TRUE);
// }

t_bool	update_key_value(t_varlist *env, char *key, char *value, int flag)
{
	char	*exportstr_tmp;
	char	*exportstr;
	t_bool	res;

	exportstr_tmp = ft_strjoin(key, "=");
	if (!exportstr_tmp)
		return (FALSE);
	exportstr = ft_strjoin(exportstr_tmp, value);
	if (!exportstr)
		return (free(exportstr_tmp), fatal_error("malloc", MALLOC_ERR_STR),
			FALSE);
	free(exportstr_tmp);
	res = update_variable_item(env, exportstr, flag);
	free(exportstr);
	return (res);
}

t_bool	update_variable_item(t_varlist *env, char *exportstr, t_bool flag)
{
	char		*key;
	t_shell_var	*target;

	key = get_env_key(exportstr);
	if (!key)
		return (FALSE);
	target = get_shell_var(env, key);
	if (!target)
		return (free(key), add_variable_item(env, exportstr, flag));
	free(key);
	free(target->value);
	free(target->exportstr);
	set_variable_attributes(target, flag);
	if (!set_variable_exportstr(target, exportstr))
		return (FALSE);
	if (!set_variable_value(target, exportstr))
		return (FALSE);
	return (TRUE);
}
