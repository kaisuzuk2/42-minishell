/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:05:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/31 11:06:16 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expand_utils.c 
char	*string_quote_removal(char *string, char quote);


// ### TODO: ~と?の展開


static t_bool expand_dollar(t_varlist *env, t_word_desc *desc)
{
	desc->word = expand_string_to_string(env, desc->word);
	if (!desc->word)
		return (FALSE);
	return (TRUE);
}

static t_bool	expand_squote(t_word_desc *desc)
{
	char	*rm_char;

	rm_char = string_quote_removal(desc->word, SINGLE_QUOTE_CHAR);
	if (!rm_char)
		return (FALSE);
	free(desc->word);
	desc->word = rm_char;
	return (TRUE);
}

static t_bool	expand_dquote(t_varlist *env, t_word_desc *desc)
{
	char	*rm_char;
	char	*res;

	rm_char = string_quote_removal(desc->word, DOUBLE_QUOTE_CHAR);
	if (!rm_char)
		return (FALSE);
	free(desc->word);
	desc->word = rm_char;
	return (expand_dollar(env, desc));
}

static t_bool	expand_var_token(t_varlist *env, t_word_list *list)
{
	t_bool	t;
	char	*res;

	if (!list)
		return (FALSE);
	while (list)
	{
		t = TRUE;
		if (is_s_quote(list->word))
			t = expand_squote(list->word);
		else if (is_d_quote(list->word))
			t = expand_dquote(env, list->word);
		else if (is_hasdollar(list->word))
			t = expand_dollar(env, list->word);
		if (!t)
			return (FALSE);
		list = list->next;
	}
	return (TRUE);
}

t_bool expand(t_varlist *env, t_command *command, t_shell_env *shell_env)
{
	t_command *cur;

	cur = command;
	while (cur)
	{
		if (!cur->command || !expand_var_token(env, cur->command->words))
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