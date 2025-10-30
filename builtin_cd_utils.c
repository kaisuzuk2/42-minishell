/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */   
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:30:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 16:31:01 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_pathsep(char c)
{
	return (c == '/' || c == 0);
}

t_bool is_interpret_home(t_word_list *list)
{
	if (!list && !list->word->word)
		return (TRUE);
	if (list->word->word[0] == '~' && list->word->word[1] == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool is_interpret_oldpwd(t_word_list *list)
{
	return (list && list->word->word[0] == '-' && list->word->word[1] == '\0');
}

t_bool is_interpret_cd(t_word_list * list)
{
	return (is_interpret_home(list) || is_interpret_oldpwd(list));
}

t_bool	is_same_file(const char *path1, const char *path2,
		struct stat *stp1, struct stat *stp2)
{
	struct stat	st1;
	struct stat	st2;

	if (!stp1)
	{
		if (stat(path1, &st1))
			return (0);
		stp1 = &st1;
	}
	if (!stp2)
	{
		if (stat(path2, &st2))
			return (0);
		stp2 = &st2;
	}
	return ((stp1->st_dev == stp2->st_dev) && (stp1->st_ino == stp2->st_ino));
}

t_bool	is_absolute_pathname(const char *string)
{
	if (string == 0 || *string == '\0')
		return (FALSE);
	if (*string == '/')
		return (TRUE);
	if (string[0] == '.' && is_pathsep(string[1]))
		return (TRUE);
	if (string[0] == '.' && string[1] == '.' && is_pathsep(string[2]))
		return (TRUE);
	return (FALSE);
}

t_bool	valid_cd_path(t_word_list *list)
{
	if (list && list->next)
		return (builtin_error("cd", NULL, ARGNUM_ERR_STR), FALSE);
	return (TRUE);
}