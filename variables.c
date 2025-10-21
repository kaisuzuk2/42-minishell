/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:02:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/21 10:50:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO: exportフラグチェック
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
		res[i] = savestring(env->list->exportstr);	
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

static t_shell_var *list_getshell_var(t_varlist *env, char *key)
{
	while (env->next)
	{
		if (!ft_strcmp(env->list->name, key))
			return (env->list);
		env = env->next;
	}
	return (NULL);
}

t_bool bind_variable(t_varlist *env, char *key, char *value)
{
	t_shell_var *shellvar;

	shellvar = list_getshell_var(env, key);
	if (!shellvar)
		return (FALSE); // ### TODO: エラー処理
	free(shellvar->value);
	shellvar->value = savestring(value); // ### TODO: エラー処理
	return (0); 
}

// ### TODO: フラグチェック
char *list_getenv(t_varlist *env, char *key)
{
	while (env->next)
	{
		if (!ft_strcmp(env->list->name, key)) // ### TODO: strcmpでいいか確認
			return (env->list->value);
		env = env->next;
	}
	return (NULL);
}

t_shell_var	*create_shell_var(void)
{
	t_shell_var	*shell_variables;

	shell_variables = (t_shell_var *)ft_calloc(sizeof(t_shell_var), 1);
	if (!shell_variables)
		return (NULL); // ### TODO: エラー処理
	return (shell_variables);
}

t_varlist	*create_varlist(void)
{
	t_varlist	*varlist;

	varlist = (t_varlist *)ft_calloc(sizeof(t_varlist), 1);
	if (!varlist)
		return (NULL); // ### TODO: エラー処理
	return (varlist);
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

t_varlist	*set_variable_item(t_varlist *head, char **envp)
{
	t_varlist	*cur;
	int			i;

	cur = head;
	i = 0;
	while (envp[i])
	{
		cur->list = create_shell_var();
		if (!cur->list)
			return (NULL); // ### TODO: エラー処理
		if (!set_variable_value(cur->list, envp[i]))
			return (NULL);
		if (!set_variable_name(cur->list, envp[i]))
			return (NULL);
		if (!set_variable_exportstr(cur->list, envp[i]))
			return (NULL);
		set_variable_attributes(cur->list);
		cur->next = create_varlist();
		if (!cur->next)
			return (NULL); // ### TODO: エラー処理
		cur = cur->next;
		i++;
	}
	return (head);
}

t_varlist	*initialize_shell_variables(char **envp)
{
	t_varlist *head;

	head = (t_varlist *)ft_calloc(sizeof(t_varlist), 1);
	if (!head)
		return (NULL);                      // ### TODO: エラー処理
	return (set_variable_item(head, envp)); // ### TODO: エラー処理
}