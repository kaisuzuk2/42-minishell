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

t_bool is_interpret_home(t_word_list *list)
{
	return (!list || !list->word->word);
}

t_bool is_interpret_oldpwd(t_word_list *list)
{
	return (list && list->word->word[0] == '-' && list->word->word[1] == '\0');
}

t_bool is_interpret_cd(t_word_list * list)
{
	return (is_interpret_home(list) || is_interpret_oldpwd(list));
}

t_bool	valid_cd_path(t_word_list *list)
{
	if (list && list->next)
		return (builtin_error("cd", NULL, ARGNUM_ERR_STR), FALSE);
	return (TRUE);
}