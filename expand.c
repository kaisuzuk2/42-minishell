/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:05:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 09:18:53 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exoand_utils.c
// char			*join_and_free(char *s1, char *s2);
// char			*join_string(char *res,
// 					char **document, t_varlist *env);
// char			*expand_quote_and_value(char **document_p, char *document,
// 					t_shell_env *shell_env);
// t_bool			word_splitting_internal(t_word_list **list_p, t_word_list *list,
// 					char **ifs_split);

// // expand_quote_removal.c
// char			*string_quote_removal(char *string, char quote);

// // expand_word_splitting.c
// char			**ifs_split(char const *s);

// expand_utils.c
t_bool	word_splitting_internal(t_word_list **list_p, t_word_list *list,
		char **ifs_split);
char	*expand_quote_and_value(char **document_p, char *document,
		t_shell_env *shell_env);
char	*join_and_free(char *s1, char *s2);



static t_bool	word_splitting(t_word_list **list_p, t_word_list *list,
		char **document_p, t_shell_env *shell_env)
{
	char		**words;
	int			varlen;
	char		*value;
	t_word_list	*next;

	varlen = get_varlen(&(*document_p)[1]);
	value = get_varvalue(shell_env, *document_p);
	if (!value)
		return (FALSE);
	words = ifs_split(value);
	free(value);
	if (!words)
		return (FALSE);
	next = list->next;
	if (!word_splitting_internal(list_p, list, words))
		return (dispose_char_arr(words), FALSE);
	dispose_char_arr(words);
	(*document_p) += (varlen + 1);
	return (TRUE);
}

static t_bool	expand_and_word_splitting_internal(char *document, t_word_list **list_p,
		t_word_list *list, t_shell_env *shell_env)
{
	char	*document_p;
	char	*tmp;

	document_p = document;
	while (*document)
	{
		if (is_quote(*document) || *document != DOLLAR_CHAR)
		{
			if (is_quote(*document))
				tmp = join_and_free((*list_p)->word->word,
						expand_quote_and_value(&document, document, shell_env));
			else
				tmp = join_string((*list_p)->word->word,
						&document, shell_env->env);
			if (!tmp)
				return (FALSE);
			(*list_p)->word->word = tmp;
		}
		else if (!word_splitting(list_p, list, &document, shell_env))
			return (FALSE);
	}
	free(document_p);
	return (TRUE);
}

static t_bool	expand_and_word_splitting(t_word_list **list_p, t_word_list *list,
		t_shell_env *shell_env)
{
	int		i;
	int		varlen;
	char	*document;

	document = ft_strdup((*list_p)->word->word);
	if (!document)
		return (FALSE);
	free((*list_p)->word->word);
	(*list_p)->word->word = ft_strdup("");
	if (!(*list_p)->word->word)
		return (free(document), FALSE);
	return (expand_and_word_splitting_internal(document, list_p, list,
			shell_env));
}

static t_bool	expand_var_token(t_word_list *list, t_shell_env *shell_env)
{
	while (list)
	{
		expand_and_word_splitting(&list, list, shell_env);
		list = list->next;
	}
	return (TRUE);
}

t_bool	expand(t_command *command, t_shell_env *shell_env)
{
	t_command	*cur;

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
