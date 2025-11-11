/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:28:03 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/11 15:23:53 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*join_string_until_varvalue_and_quote(char *res, char **document)
{
	char	*doll_ptr;
	char	*tmp;
	char	*res_tmp;
	int		i;

	i = 0;
	while ((*document)[i] && (*document)[i] != '$' && (*document)[i] != '\''
		&& (*document)[i] != '\"')
		i++;
	tmp = ft_substr(*document, 0, i);
	if (!tmp)
		return (free(res), NULL);
	res_tmp = join_and_free(res, tmp);
	*document = &(*document)[i];
	return (res_tmp);
}

static char	*expand_quote(char **document_p, char *document)
{
	char	quote;
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	quote = document[i++];
	while (document[i] != quote)
		i++;
	tmp = ft_substr(document, 0, i);
	if (!tmp)
		return (NULL);
	res = string_quote_removal(tmp, quote);
	if (!res)
		return (free(tmp), NULL);
	free(tmp);
	*document_p = &document[i + 1];
	return (res);
}

char	*expand_quote_and_value(char **document_p, char *document,
		t_shell_env *shell_env)
{
	char *res;
	int		i;
	char	*rm_quote_doc;
	char	quote;

	quote = document[0];
	rm_quote_doc = expand_quote(document_p, document);
	if (!rm_quote_doc)
		return (NULL);
	if (quote == SINGLE_QUOTE_CHAR || !ft_strchr(rm_quote_doc, '$'))
		return (rm_quote_doc);
	i = 0;
	// while (rm_quote_doc[i] != '$')
	// 	i++;
	// doc = ft_substr(rm_quote_doc, 0, i);
	// if (!doc)
	// 	return (free(rm_quote_doc), NULL);
	// val = get_varvalue(shell_env, &rm_quote_doc[i]);
	// if (!get_varvalue)
	// 	return (free(rm_quote_doc), free(doc), NULL);
	// free(rm_quote_doc);
	res = expand_string_to_string(rm_quote_doc, shell_env);
	// return (join_and_free(doc, val));
	return (res);
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
	while (ifs_split[i])
	{
		new = (t_word_list *)xcalloc(sizeof(t_word_list), 1);
		if (!new)
			return (FALSE);
		new->word = (t_word_desc *)xcalloc(sizeof(t_word_desc), 1);
		if (!new->word)
			return (free(new), FALSE);
		new->word->word = savestring(ifs_split[i++]);
		if (!new->word->word)
			return (dispose_desc_words(new), FALSE);
		list->next = new;
		list = list->next;
	}
	list->next = next;
	(*list_p) = list;
	return (TRUE);
}