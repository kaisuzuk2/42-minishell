/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_specials.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:55:03 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/28 10:45:49 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	init_pwd(t_shell_env *shell_env)
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

t_bool	init_shlvl(t_shell_env *shell_env)
{
	t_shell_var	*var;

	var = get_shell_var(shell_env->env, "SHLVL");
	if (!var)
	{
		if (!update_variable_item(shell_env->env, "SHLVL=0", 1))
			return (FALSE);
		return (TRUE);
	}
	return (TRUE);
}

t_bool	update_shlvl(t_shell_env *shell_env)
{
	int			shlvl_int;
	char		*shlvl_txt;
	char		*shlvl_val;
	t_shell_var	*var;

	var = get_shell_var(shell_env->env, "SHLVL");
	if (!var)
		return (init_shlvl(shell_env));
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


t_bool	init_path(t_shell_env *shell_env, char **envp)
{
	t_varlist	*env;
	int			i;

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
