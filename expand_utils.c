/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:28:03 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/20 11:39:18 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// expand_quote_removal.c
char				*expand_quote(char **document_p, char *document);

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*join_until(char *res, char **document, t_varlist *env)
{
	char	*doll_ptr;
	char	*tmp;
	char	*res_tmp;
	int		i;
	char	*home_value;

	tmp = expand_tilda(res, document, env);
	free(res);
	res = tmp;
	if (!res)
		return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	i = 0;
	while ((*document)[i] && (*document)[i] != '$' && (*document)[i] != '\''
		&& (*document)[i] != '\"')
		i++;
	tmp = ft_substr(*document, 0, i);
	if (!tmp)
		return (free(res),fatal_error("malloc", MALLOC_ERR_STR) ,NULL);
	res_tmp = join_and_free(res, tmp);
	*document = &(*document)[i];
	return (res_tmp);
}

char	*expand_quote_and_value(char **document_p, char *document,
		t_shell_env *shell_env)
{
	char	*res;
	char	*rm_quote_doc;
	char	quote;

	quote = document[0];
	rm_quote_doc = expand_quote(document_p, document);
	if (!rm_quote_doc)
		return (NULL);
	if (quote == SINGLE_QUOTE_CHAR || !ft_strchr(rm_quote_doc, '$'))
		return (rm_quote_doc);
	res = expand_string_to_string(rm_quote_doc, rm_quote_doc, shell_env);
	return (res);
}

static t_word_list	*new_node(char *ifs_split)
{
	t_word_list	*new;

	new = (t_word_list *)xcalloc(sizeof(t_word_list), 1);
	if (!new)
		return (NULL);
	new->word = (t_word_desc *)xcalloc(sizeof(t_word_desc), 1);
	if (!new->word)
		return (free(new), NULL);
	new->word->word = savestring(ifs_split);
	if (!new->word->word)
		return (dispose_desc_words(new), NULL);
	return (new);
}

t_bool	word_splitting_internal(t_word_list **list_p, t_word_list *list,
		char **ifs_split)
{
	t_word_list	*next;
	t_word_list	*new;
	int			i;

	next = list->next;
	i = 0;
	if (!*ifs_split)
		return (TRUE);
	list->word->word = join_and_free(list->word->word,
			savestring(ifs_split[i++]));
	if (!list->word->word)
		return (fatal_error("malloc", MALLOC_ERR_STR), FALSE);
	while (ifs_split[i])
	{
		new = new_node(ifs_split[i]);
		if (!new)
			return (fatal_error("malloc", MALLOC_ERR_STR), FALSE);
		list->next = new;
		list = list->next;
		i++;
	}
	list->next = next;
	(*list_p) = list;
	return (TRUE);
}
