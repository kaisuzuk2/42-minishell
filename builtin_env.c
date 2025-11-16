/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:26:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 10:22:16 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_printenv(t_varlist *env)
{
	while (env)
	{
		if (!env->var->value || !is_exported(env->var))
		{
			env = env->next;
			continue ;
		}
		ft_dprintf(STDOUT_FILENO, "%s\n", env->var->exportstr);
		env = env->next;
	}
	return (EXECUTION_SUCCESS);
}

int	builtin_env(t_word_list *list, t_shell_env *shell_env)
{
	if (list)
		return (builtin_error("env", list->word->word, NOSUP_ARG_ERR),
			EX_NOTFOUND);
	return (builtin_printenv(shell_env->env));
}
