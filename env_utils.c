/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:27:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 17:35:23 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_env_arr(t_varlist *env)
{
	const size_t len = list_length((t_generic_list *)env);
	char **res;
	int i;

	res = (char **)malloc(sizeof(char *) * len);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		res[i] = savestring(env->var->exportstr);	
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

t_shell_var *list_getshell_var(t_varlist *env, char *key)
{
	while (env->next)
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
	while (env->next)
	{
		if (!ft_strcmp(env->var->name, key)) // ### TODO: strcmpでいいか確認
			return (env->var->value);
		env = env->next;
	}
	return (NULL);
}

t_bool add_variable_item(t_varlist *env, char *exportstr)
{
	while (env->next)
		env = env->next;
	if (!set_variable_name(env->var, exportstr))
		return (FALSE);
	if (!set_variable_value(env->var, exportstr))
		return (FALSE);
	if (!set_variable_exportstr(env->var, exportstr))
		return (FALSE);
	set_variable_attributes(env->var);	
	env->next = create_varlist();
	if (!env->next)
		return (FALSE); // ### TODO: エラー処理
	env->next->var = create_shell_var();
	if (!env->next->var)
		return (FALSE); // ### TODO: エラー処理
	return (TRUE);
}