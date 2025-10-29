/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:26:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 10:12:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int builtin_printenv(t_varlist *env)
{
	char **envstr;
	int i;

	i = 0;
	envstr = get_env_arr(env);
	if (!envstr)
		return (EX_FATAL_ERROR);
	while (envstr[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", envstr[i]);
		free(envstr[i]);
		i++;
	}
	free(envstr);
	return (EXECUTION_SUCCESS);
}

int builtin_env(t_word_list *list, t_shell_env *shell_env)
{
	if (list)
		return (builtin_error("env", list->word->word, NOSUP_ARG_ERR), EX_NOTFOUND);
	return (builtin_printenv(shell_env->env));
}