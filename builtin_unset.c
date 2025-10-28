/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:32:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 14:11:08 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://atmarkit.itmedia.co.jp/ait/articles/1905/24/news015.html
/*

先頭の要素だった場合

*/
static int unbind_varlist(t_word_list *list, t_varlist *env)
{
	const char *word = list->word->word;

	t_varlist *cur;
	t_varlist *t;

	cur = env;
	while (ft_strcmp(cur->next->var->name, word))// ### TODO: strcmpでいいか確認
	{
		cur = cur->next;
		if (!cur)
		{
			return (0);
		}
	}
	t = cur->next;
	cur->next = t->next;
	free(t->var->name);
	free(t->var->value);
	free(t->var->exportstr);
	free(t->var);
	free(t);
	return (0);
}

int builtin_unset(t_word_list *list, t_shell_env *shell_env)
{
	if (!list)
		return (0);
	return (unbind_varlist(list,shell_env->env));
}