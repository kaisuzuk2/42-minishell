/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:05:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/09 15:35:22 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expand_utils.c 
char	*string_quote_removal(char *string, char quote);

// expand_word_splitting.c
char	**command_split(char const *s);


// subst.c
t_bool expand_string_with_quote(t_word_list **list_p, t_word_list *list, t_shell_env *shell_env);
char	*join_string_until_varvalue(char *res, char **document);


// ### TODO: ~と?の展開

static t_bool expand_var_token(t_word_list *list, t_shell_env *shell_env)
{

	while (list)
	{
		expand_string_with_quote(&list, list, shell_env);
		list = list->next;
	}
	return (TRUE);
}

t_bool expand(t_command *command, t_shell_env *shell_env)
{
	t_command *cur;

	cur = command;
	while (cur)
	{
		if (!cur->command || !expand_var_token(cur->command->words, shell_env))
		{
			dispose_command(command);
			dispose_env(shell_env);
			fatal_error("malloc", MALLOC_ERR_STR);
			exit(1);
		}
		cur = cur->next;
	}
	return (TRUE);
}