/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:37:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 15:52:55 by kaisuzuk         ###   ########.fr       */
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

// int builtin_export(t_word_list *list, t_shell_env *shell_env)
// {
// 	t_varlist *env;

// 	env = shell_env->env;
// 	if (!list)
// 		return (show_var_attributes(env));
// 	while (env->next)
// 		env = env->next;
// 	if (!set_variable_value(env->var, list->word->word))
// 		return (99); // ### TODO: エラー処理
// 	if (!set_variable_name(env->var, list->word->word))
// 		return (99); // ### TODO: エラー処理
// 	if (!set_variable_exportstr(env->var, list->word->word))
// 		return (99); // ### TODO: エラー処理
// 	set_variable_attributes(env->var);
// 	env->next = create_varlist();
// 	if (!env->next)
// 		return (99); // ### TODO: エラー処理
// 	env->next->var = create_shell_var();
// 	if (!env->next->var)
// 		return (99); // ### TODO: エラー処理
// 	return (1);
// }

static t_bool is_valid_env_name(char *exportstr)
{
	if (ft_isdigit(*exportstr))
		return (FALSE);
	while (*exportstr)
	{
		if (!ft_isalnum(*exportstr) && !(*exportstr == '_'))
			return (FALSE);
		exportstr++;
	}
	return (TRUE);
}

int builtin_export(t_word_list *list, t_shell_env *shell_env)
{
	t_varlist *env;
	t_bool flg;

	if (!list)
		return (show_var_attributes(env));
	flg = TRUE;
	while (list)
	{
		if (!is_valid_env_name(list->word->word))
		{
			flg = FALSE;
			builtin_error("export", list->word->word, EXPORT_ERR);
			list = list->next;
			continue ;
		}
		if (update_variable_item(shell_env->env, list->word->word))
			return (EX_FATAL_ERROR);
		list = list->next;
	}
	if (!flg)
		return (EXECUTION_FAILURE);
	return (EXECUTION_SUCCESS);
}