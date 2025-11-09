/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:05:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/05 12:55:31 by kaisuzuk         ###   ########.fr       */
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


// static t_bool expand_dollar(t_word_desc *desc, t_shell_env *shell_env)
// {
// 	desc->word = expand_string_to_string(desc->word, shell_env);
// 	if (!desc->word)
// 		return (FALSE);
// 	return (TRUE);
// }

// static t_bool	expand_squote(t_word_desc *desc)
// {
// 	char	*rm_char;

// 	rm_char = string_quote_removal(desc->word, SINGLE_QUOTE_CHAR);
// 	if (!rm_char)
// 		return (FALSE);
// 	free(desc->word);
// 	desc->word = rm_char;
// 	return (TRUE);
// }

// static t_bool	expand_dquote(t_word_desc *desc, t_shell_env *shell_env)
// {
// 	char	*rm_char;
// 	char	*res;

// 	rm_char = string_quote_removal(desc->word, DOUBLE_QUOTE_CHAR);
// 	if (!rm_char)
// 		return (FALSE);
// 	free(desc->word);
// 	desc->word = rm_char;
// 	return (expand_dollar(desc, shell_env));
// }

// static t_bool word_splitting(t_word_list *list, t_shell_env *shell_env)
// {
// 	char **ifs_split;
// 	int i;
// 	t_word_list *next;

// 	if (!expand_dollar(list->word, shell_env))
// 		return (FALSE);
// 	ifs_split = command_split(list->word->word);
// 	if (!ifs_split)
// 		return (FALSE);
// 	next = list->next;
// 	i = 0;
// 	while (ifs_split[i])
// 	{
// 		dispose_word(list->word);
// 		list->word = (t_word_desc *)xcalloc(sizeof(t_word_desc), 1);
// 		if (!list->word)
// 			return (FALSE);
// 		list->word->word = savestring(ifs_split[i]);
// 		if (!list->word->word)
// 			return (FALSE);
// 		list->word->kind = TK_WORD;
// 		if (ifs_split[i + 1])
// 		{
// 			list->next = (t_word_list *)xcalloc(sizeof(t_word_list), 1);
// 			if (!list->next)
// 				return (FALSE);
// 			list = list->next;
// 		}
// 		i++;
// 	}
// 	list->next = next;
// 	return (TRUE);
// }

// static t_bool	expand_var_token(t_word_list *list, t_shell_env *shell_env)
// {
// 	t_bool	t;
// 	char	*res;

// 	if (!list)
// 		return (FALSE);
// 	while (list)
// 	{
// 		t = TRUE;
// 		// if (is_s_quote(list->word))
// 		// 	t = expand_squote(list->word);
// 		// else if (is_d_quote(list->word))
// 		// 	t = expand_dquote(list->word, shell_env);
// 		// else if (is_hasdollar(list->word))
// 		// 	t = word_splitting(list, shell_env);
// 		// if (!t)
// 		// 	return (FALSE);
// 		list->word->word = expand_string_width_quote(list->word->word, shell_env);
// 		list = list->next;
// 	}
// 	return (TRUE);
// }


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