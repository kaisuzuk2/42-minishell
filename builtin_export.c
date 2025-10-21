/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:37:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/21 14:32:46 by kaisuzuk         ###   ########.fr       */
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

int builtin_export(t_word_list *list, t_varlist *env)
{
	if (!list)
		return (show_var_attributes(env));
	while (env->next)
		env = env->next;
	if (!set_variable_value(env->list, list->word->word))
		return (99); // ### TODO: エラー処理
	if (!set_variable_name(env->list, list->word->word))
		return (99); // ### TODO: エラー処理
	if (!set_variable_exportstr(env->list, list->word->word))
		return (99); // ### TODO: エラー処理
	set_variable_attributes(env->list);
	env->next = create_varlist();
	if (!env->next)
		return (99); // ### TODO: エラー処理
	env->next->list = create_shell_var();
	if (!env->next->list)
		return (99); // ### TODO: エラー処理
	return (1);
}