/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:27:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 08:55:26 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool			set_variable_items(t_shell_var *var, char *exportstr, int flg);

t_bool	is_exported(t_shell_var *env_var)
{
	if (!env_var)
		return (FALSE);
	return (env_var->attributes);
}

t_bool	is_underbar(t_shell_var *env_var)
{
	if (!env_var)
		return (FALSE);
	return (env_var->name[0] == '_' && env_var->name[1] == '\0');
}

static t_bool	add_variable_item(t_varlist *env, char *exportstr, int flag)
{
	t_varlist	*cur;

	while (env->next)
		env = env->next;
	env->next = create_varlist();
	if (!env->next)
		return (FALSE);
	env = env->next;
	env->var = create_shell_var();
	if (!env->var)
		return (FALSE);
	if (!set_variable_items(env->var, exportstr, flag))
		return (FALSE);
	return (TRUE);
}

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
