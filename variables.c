/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:02:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/19 10:01:48 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	set_variable_name(t_shell_var *map, char *env)
{
	char	*name_ptr;

	name_ptr = ft_strchr(env, '='); // ### TODO: マクロ化
	if (!name_ptr)
		map->name = env;
	else
	{
		*name_ptr = '\0';
		map->name = env;
	}
}

// ### TODO: nameを先に設定するとvalueが設定できなくなる
void	set_variable_value(t_shell_var *map, char *env)
{
	char	*value_ptr;

	value_ptr = ft_strchr(env, '=');
	if (!value_ptr)
		return ;
	value_ptr++;
	map->value = value_ptr;
}

void	set_variable_exportstr(t_shell_var *map, char *env)
{
	map->exportstr = env;
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
		set_variable_value(cur->list, envp[i]);
		set_variable_name(cur->list, envp[i]);
		set_variable_exportstr(cur->list, envp[i]);
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