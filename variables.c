/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:02:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 12:12:39 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dispose_env.c
void			dispose_varlist(t_varlist *list);

static t_bool	set_variable_item_internal(t_shell_var *var, char *envp_str)
{
	if (!set_variable_value(var, envp_str))
		return (FALSE);
	if (!set_variable_name(var, envp_str))
		return (FALSE);
	if (!set_variable_exportstr(var, envp_str))
		return (FALSE);
	set_variable_attributes(var, 1);
	return (TRUE);
}

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
		if (!cur->next)
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
	char	*pwd_value;
	char	*pwd;

	pwd_value = getcwd(NULL, 0);
	if (!pwd_value)
		return (sys_error("getcwd failed"), FALSE);
	shell_env->tcwd = savestring(pwd_value);
	if (!shell_env->tcwd)
		return (free(pwd_value), FALSE);
	pwd = ft_strjoin("PWD=", pwd_value);
	if (!pwd)
		return (free(pwd_value), fatal_error("malloc", MALLOC_ERR_STR), FALSE);
	free(pwd_value);
	if (!update_variable_item(shell_env->env, pwd, 1))
		return (free(pwd), FALSE);
	free(pwd);
	if (!update_variable_item(shell_env->env, "OLDPWD=", 1))
	return (TRUE);
}

static t_bool init_path(t_shell_env *shell_env)
{
	t_varlist *env;

	env = create_varlist();
	if (!env)
		return (FALSE);
	shell_env->env = env;
	env->var = create_shell_var();
	if (!env->var)
		return (FALSE);
	if (!set_variable_name(env->var, DF_PATH))
		return (FALSE);
	if (!set_variable_value(env->var, DF_PATH))
		return (FALSE);
	if (!set_variable_exportstr(env->var, DF_PATH))
		return (FALSE);
	set_variable_attributes(env->var, 0);
	return (TRUE);
}

t_shell_env	*initialize_shell_variables(char **envp)
{
	t_shell_env	*shell_env;

	shell_env = (t_shell_env *)xcalloc(sizeof(t_shell_env), 1);
	if (!shell_env)
		return (NULL);
	if (!*envp)
	{
		if (!init_path(shell_env))
		{
			dispose_env(shell_env);
			exit(1);
		}
	}
	else
		shell_env->env = set_variable_item(envp);
	if (!shell_env->env)
	{
		dispose_env(shell_env);
		exit(1);
	}
	if (!init_pwd(shell_env))
	{
		dispose_env(shell_env);
		exit(1);
	}
	set_last_status(EXECUTION_SUCCESS, shell_env);
	return (shell_env);
}
