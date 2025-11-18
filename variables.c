/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:02:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 16:42:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dispose_env.c
void			dispose_varlist(t_varlist *list);
t_bool			set_variable_items(t_shell_var *var, char *exportstr, int flg);

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

static t_varlist	*set_variable_item(t_shell_env *shell_env, char **envp)
{
	t_varlist	head;
	t_varlist	*cur;
	int			i;

	cur = &head;
	if (shell_env->env)
	{
		cur->next = shell_env->env;
		cur = cur->next;
	}
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
	pwd = ft_strjoin(PWD_KEY, pwd_value);
	if (!pwd)
		return (free(pwd_value), fatal_error("malloc", MALLOC_ERR_STR), FALSE);
	free(pwd_value);
	if (!update_variable_item(shell_env->env, pwd, 1))
		return (free(pwd), FALSE);
	free(pwd);
	if (get_shell_var(shell_env->env, OLDPWD))
		return (TRUE);
	if (!update_variable_item(shell_env->env, OLDPWD_KEY, 1))
		return (FALSE);
	return (TRUE);
}

static t_bool	init_path(t_shell_env *shell_env, char **envp)
{
	t_varlist	*env;
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], PATH_KEY, ft_strlen(PATH_KEY)))
			return (TRUE);
		i++;
	}
	env = create_varlist();
	if (!env)
		return (FALSE);
	shell_env->env = env;
	env->var = create_shell_var();
	if (!env->var)
		return (FALSE);
	set_variable_items(env->var, DF_PATH, 0);
	return (TRUE);
}

static t_bool	init_shlvl(t_shell_env *shell_env)
{
	t_shell_var	*var;
	int			shlvl_int;
	char		*shlvl_txt;
	char		*shlvl_val;

	var = get_shell_var(shell_env->env, "SHLVL");
	if (!var)
	{
		if (!update_variable_item(shell_env->env, "SHLVL=0", 1))
			return (FALSE);
		return (TRUE);
	}
	shlvl_int = ft_atoi(var->value);
	shlvl_int++;
	shlvl_val = ft_itoa(shlvl_int);
	if (!shlvl_val)
		return (FALSE);
	shlvl_txt = create_exportstr("SHLVL", shlvl_val);
	if (!shlvl_txt)
		return (free(shlvl_val), FALSE);
	free(shlvl_val);
	if (!update_variable_item(shell_env->env, shlvl_txt, 1))
		return (free(shlvl_txt), FALSE);
	free(shlvl_txt);
	return (TRUE);
}

static void	handle_variables_error(t_shell_env *shell_env)
{
	dispose_env(shell_env);
	exit(EXECUTION_FAILURE);
}

t_shell_env	*initialize_shell_variables(char **envp)
{
	t_shell_env	*shell_env;

	shell_env = (t_shell_env *)xcalloc(sizeof(t_shell_env), 1);
	if (!shell_env)
		return (NULL);
	// if (!*envp)
	// {
	// 	if (!init_path(shell_env, envp))
	// 		handle_variables_error(shell_env);
	// }
	// else
	if (!init_path(shell_env, envp))
		handle_variables_error(shell_env);
	shell_env->env = set_variable_item(shell_env, envp);
	if (!shell_env->env)
		handle_variables_error(shell_env);
	if (!init_pwd(shell_env))
		handle_variables_error(shell_env);
	if (!init_shlvl(shell_env))
		handle_variables_error(shell_env);
	set_last_status(EXECUTION_SUCCESS, shell_env);
	return (shell_env);
}
