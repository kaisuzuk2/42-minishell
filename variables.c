/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:02:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 08:52:24 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO: exportフラグチェック

// dispose_env.c
void			dispose_varlist(t_varlist *list);

t_bool	bind_variable(t_varlist *env, char *key, char *value)
{
	t_shell_var	*shellvar;

	shellvar = list_getshell_var(env, key);
	if (!shellvar)
		return (FALSE); // ### TODO: エラー処理
	free(shellvar->value);
	shellvar->value = savestring(value); // ### TODO: エラー処理
	return (0);
}

// t_varlist	*set_variable_item(t_varlist *head, char **envp)
// {
// 	t_varlist	*cur;
// 	int			i;

// 	cur = head;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		cur->var = create_shell_var();
// 		if (!cur->var)
// 			return (NULL); // ### TODO: エラー処理
// 		if (!set_variable_value(cur->var, envp[i]))
// 			return (NULL);
// 		if (!set_variable_name(cur->var, envp[i]))
// 			return (NULL);
// 		if (!set_variable_exportstr(cur->var, envp[i]))
// 			return (NULL);
// 		set_variable_attributes(cur->var);
// 		cur->next = create_varlist();
// 		if (!cur->next)
// 			return (NULL); // ### TODO: エラー処理
// 		cur->next->var = create_shell_var();
// 		if (!cur->next->var)
// 			return (NULL);
// 		cur = cur->next;
// 		i++;
// 	}
// 	return (head);
// }

static t_bool	set_variable_item_internal(t_shell_var *var, char *envp_str)
{
	if (!set_variable_value(var, envp_str))
		return (FALSE);
	if (!set_variable_name(var, envp_str))
		return (FALSE);
	if (!set_variable_exportstr(var, envp_str))
		return (FALSE);
	set_variable_attributes(var);
	return (TRUE);
}

// 先頭のポインタを返す
t_varlist	*set_variable_item(char **envp)
{
	t_varlist	head;
	t_varlist	*cur;
	int			i;

	cur = &head;
	i = 0;
	while (envp[i])
	{
		cur->next = create_varlist();
		if (!cur->var)
			return (dispose_varlist(head.next), NULL);
		cur = cur->next;
		cur->var = create_shell_var();
		if (!cur->var)
			return (dispose_varlist(head.next), NULL);
		if (!set_variable_item_internal(cur->var, envp[i]))
			return (dispose_varlist(head.next), NULL);
		i++;
	}
	return (head.next);
}

static t_bool	init_pwd(t_shell_env *shell_env)
{
	char	*pwd;

	pwd = list_getenv(shell_env->env, "PWD");
	if (!pwd)
	{
		shell_env->tcwd = getcwd(NULL, 0);
		if (!shell_env->tcwd)
			return (sys_error("getcwd failed"), FALSE);
		pwd = ft_strjoin("PWD=", shell_env->tcwd);
		if (!pwd)
			return (fatal_error("malloc", MALLOC_ERR_STR), FALSE);
		add_variable_item(shell_env->env, pwd); // ### TODO: エラー処理
		return (TRUE);
	}
	shell_env->tcwd = savestring(pwd);
	if (!shell_env->tcwd)
		return (FALSE);
	return (TRUE);
}

// ### TODO: 全体のエラー処理
// t_shell_env	*initialize_shell_variables(char **envp)
// {
// 	t_shell_env *shell_env;

// 	shell_env = (t_shell_env *)ft_calloc(sizeof(t_shell_env), 1);
// 	if (!shell_env)
// 		return (NULL);
// 	shell_env->env = create_varlist();
// 	if (!shell_env->env)
// 		return (NULL);                      // ### TODO: エラー処理
// 	shell_env->env = set_variable_item(shell_env->env, envp);
// 	if (!shell_env->env)
// 		return (NULL);
// 	if (!init_pwd(shell_env))
// 		return (printf("### here\n"), NULL);
// 	return (shell_env);
// }

t_shell_env	*initialize_shell_variables(char **envp)
{
	t_shell_env	*shell_env;

	shell_env = (t_shell_env *)xmalloc(sizeof(t_shell_env));
	if (!shell_env)
		return (NULL);
	shell_env->env = set_variable_item(envp);
	if (!shell_env->env)
	{
		dispose_env(shell_env);
		exit(1);
	}
	return (shell_env);
}
