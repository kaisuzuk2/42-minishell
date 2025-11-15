/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:32:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 12:32:11 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_delone(t_varlist *cur)
{
	t_varlist	*t;

	t = cur->next;
	cur->next = t->next;
	dispose_shell_var(t->var);
	free(t);
}

static t_varlist	*unset_env(char *key, t_varlist *env)
{
	t_varlist	*t;
	t_varlist	*head;

	if (!list_getshell_var(env, key))
		return (env);
	if (!ft_strcmp(env->var->name, key))
	{
		t = env;
		env = env->next;
		dispose_shell_var(t->var);
		free(t);
		return (env);
	}
	head = env;
	while (env->next)
	{
		if (!ft_strcmp(env->next->var->name, key))
			return (env_delone(env), head);
		env = env->next;
	}
	return (head);
}

int	builtin_unset(t_word_list *list, t_shell_env *shell_env)
{
	while (list)
	{
		shell_env->env = unset_env(list->word->word, shell_env->env);
		list = list->next;
	}
	return (EXECUTION_SUCCESS);
}
