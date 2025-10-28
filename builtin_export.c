/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:37:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 14:09:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO: 設定がすでにされている場合のケース

static int show_var_attributes(t_varlist *env)
{
	char **envstr;
	int i;

	envstr = get_env_arr(env); // ### TODO: エラー処理
	if (!envstr)
		return (99);
	i = 0;
	while (envstr[i])
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s\n", envstr[i]);
		i++;
	}
	return (1);
}

int builtin_export(t_word_list *list, t_shell_env *shell_env)
{
	t_varlist *env;

	env = shell_env->env;
	if (!list)
		return (show_var_attributes(env));
	while (env->next)
		env = env->next;
	if (!set_variable_value(env->var, list->word->word))
		return (99); // ### TODO: エラー処理
	if (!set_variable_name(env->var, list->word->word))
		return (99); // ### TODO: エラー処理
	if (!set_variable_exportstr(env->var, list->word->word))
		return (99); // ### TODO: エラー処理
	set_variable_attributes(env->var);
	env->next = create_varlist();
	if (!env->next)
		return (99); // ### TODO: エラー処理
	env->next->var = create_shell_var();
	if (!env->next->var)
		return (99); // ### TODO: エラー処理
	return (1);
}