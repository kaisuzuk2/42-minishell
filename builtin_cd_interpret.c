/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_interpret.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:55:51 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 16:09:40 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_interpret_oldpwd(t_word_list *list)
{
	return (list && list->word->word[0] == '-' && list->word->word[1] == '\0');
}

t_bool	is_interpret_home(t_word_list *list)
{
	if (!list)
		return (TRUE);
	if (list->word->word[0] == '~' && list->word->word[1] == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	is_interpret_cd(t_word_list *list)
{
	return (is_interpret_home(list) || is_interpret_oldpwd(list));
}

char	*get_interpret_cd(t_word_list *list, t_varlist *env)
{
	char	*dirname;

	if (is_interpret_home(list))
	{
		dirname = get_listenv(env, "HOME");
		if (!dirname)
		{
			builtin_error("cd", NULL, "HOME not set");
			return (NULL);
		}
	}
	else
	{
		dirname = get_listenv(env, OLDPWD);
		if (!dirname)
		{
			builtin_error("cd", NULL, "OLDPWD not set");
			return (NULL);
		}
	}
	return (dirname);
}
