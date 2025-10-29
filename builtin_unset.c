/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:32:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 14:47:56 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://atmarkit.itmedia.co.jp/ait/articles/1905/24/news015.html
/*

先頭の要素だった場合

*/
// static int unbind_varlist(t_word_list *list, t_varlist *env)
// {
// 	const char *word = list->word->word;

// 	t_varlist *cur;
// 	t_varlist *t;

// 	cur = env;
// 	while (ft_strcmp(cur->next->var->name, word))// ### TODO: strcmpでいいか確認
// 	{
// 		cur = cur->next;
// 		if (!cur)
// 		{
// 			return (0);
// 		}
// 	}
// 	t = cur->next;
// 	cur->next = t->next;
// 	free(t->var->name);
// 	free(t->var->value);
// 	free(t->var->exportstr);
// 	free(t->var);
// 	free(t);
// 	return (0);
// }

// ### TODO: strcmpでええかね？
static t_varlist *unset_env(char *key, t_varlist *env)
{
	t_varlist *t;

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
	while (env)
	{
		if (!env->next)
			break;
		if (!ft_strcmp(env->next->var->name, key))
		{
			t = env->next;
			env->next = t->next;
			dispose_shell_var(t->var);
			free(t);
			return (env);
		}
		env = env->next;
	}
	return (env);
}

int builtin_unset(t_word_list *list, t_shell_env *shell_env)
{	
	while (list)
	{
		shell_env->env = unset_env(list->word->word, shell_env->env);
		list = list->next;
	}
	return (EXECUTION_SUCCESS);
}