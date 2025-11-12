/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:27:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/12 10:46:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_last_status(int s, t_shell_env *env)
{
	env->last_status = s;
}

int get_last_status(t_shell_env *env)
{
	return (env->last_status);
}

t_bool set_current_working_directory(t_shell_env *shell_env, char *value)
{
	if (shell_env->tcwd)
		free(shell_env->tcwd);
	shell_env->tcwd = savestring(value);
	if (!shell_env->tcwd)
		return (FALSE);
	return (TRUE);
}

char *get_current_working_directory(t_shell_env *shell_env)
{
	return (shell_env->tcwd);
}

char **get_env_arr(t_varlist *env)
{
	const size_t len = list_length((t_generic_list *)env);
	char **res;
	int i;

	res = (char **)xmalloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (env)
	{
		if (!env->var->attributes)
		{
			env = env->next;
			continue ;
		}
		res[i] = savestring(env->var->exportstr);
		if (!res[i])
		{
			while (i >= 0)
			{
				free(res[i]);
				i--;
			}
			free(res);
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

static t_bool add_variable_item(t_varlist *env, char *exportstr, int flag)
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
	set_variable_attributes(env->var, flag);	
	return (TRUE);
}

t_bool update_key_value(t_varlist *env, char *key, char *value, int flag)
{
	char *exportstr_tmp;
	char *exportstr;
	t_bool res;
	exportstr_tmp = ft_strjoin(key, "=");
	if (!exportstr_tmp)
		return (FALSE);
	exportstr = ft_strjoin(exportstr_tmp, value);
	if (!exportstr)
		return (free(exportstr_tmp), fatal_error("malloc", MALLOC_ERR_STR), FALSE);
	free(exportstr_tmp);
	res = update_variable_item(env, exportstr, flag);
	free(exportstr);
	return (res);
}

t_bool update_variable_item(t_varlist *env, char *exportstr, int flag)
{
	char *key;
	t_shell_var *target;

	key = get_env_key(exportstr);
	if (!key)
		return (FALSE);
	target = list_getshell_var(env, key);
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