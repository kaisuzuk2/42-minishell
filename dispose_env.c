/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:37:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 18:42:06 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void dispose_shell_var(t_shell_var *var)
{
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	if (var->exportstr)
		free(var->exportstr);
	if (var->attributes)
		free(var->attributes);
	free(var);
}

static void dispose_t_varlist(t_varlist *list)
{
	t_varlist *t;

	while (list)
	{
		t = list;
		list = list->next;
		dispose_shell_var(t);
		free(t);
	}
}

void dispose_env(t_shell_env *shell_env)
{
	if (t_shell_env->tcwd)
		free(t_shell_env->tcwd);
	dispose_t_varlist(shell_env->env);
	free(shell_env);
}