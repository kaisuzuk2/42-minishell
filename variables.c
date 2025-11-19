/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:02:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 12:18:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// variables_specials.c
t_bool				init_path(t_shell_env *shell_env, char **envp);
t_bool				init_shlvl(t_shell_env *shell_env);
t_bool				init_pwd(t_shell_env *shell_env);

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

	memset(&head, 0, sizeof(t_varlist));
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
