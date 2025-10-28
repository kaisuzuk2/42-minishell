/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:26:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 14:27:32 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int builtin_printenv(t_varlist *env)
{
	char **envstr;
	int i;

	i = 0;
	envstr = get_env_arr(env); // ### TODO: エラー処理
	while (envstr[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", envstr[i]);
		i++;
	}
	return (1);// ### TODO: 終了ステータス考える
}

int builtin_env(t_word_list *list, t_shell_env *shell_env)
{
	if (list)
		return (99); // ### TODO: エラー処理
	return (builtin_printenv(shell_env->env));
}