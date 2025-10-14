/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:05:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/14 11:43:54 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

フラグを元に条件分岐する
1) $を展開する
2) クォートを除去する

*/

static t_bool	is_hasdollar(t_word_desc *desc)
{
	return (desc->kind == W_HASDOLLAR);
}

static char	*string_quote_removal(char *string, char quote)
{
	char	set[2];

	set[0] = quote;
	set[1] = '\0';
	return (ft_strtrim(string, set));
}

static int	get_varlen(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (!(ft_isalnum(*str)) && !(*str == '_')) // ### TODO: 条件見直す
			break ;
		res++;
		str++;
	}
	return (res);
}

static char	*get_varvalue(char *doll_ptr)
{
	char	*varname;
	char	*varvalue;

	varvalue = NULL;
	varname = ft_substr(doll_ptr + 1, 0, get_varlen(doll_ptr + 1));
	if (!varname)
		return (NULL);
	varvalue = getenv(varname);
	free(varname);
	if (!varvalue) // ### TODO: エラー処理
		return ("");
	return (varvalue);
}

static char	*join_string_until_varvalue(char *res, char **document)
{
	char	*doll_ptr;
	char	*tmp;
	char	*res_tmp;

	doll_ptr = ft_strchr(*document, '$');
	tmp = ft_substr(*document, 0, (doll_ptr - *document));
	if (!tmp)
		return (NULL);
	res_tmp = ft_strjoin(res, tmp);
	free(res);
	free(tmp);
	*document = doll_ptr + 1 + get_varlen(doll_ptr + 1);
	return (res_tmp);
}

static char	*append_remainder(char *document, char *remainder)
{
	char	*res;

	if (!remainder)
		return (document);
	res = ft_strjoin(document, remainder);
	free(document);
	return (res);
}

char	*expand_string_to_string(char *document)
{
	char	*res;
	char	*res_tmp;
	char	*document_ptr;
	char	*varvalue;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	document_ptr = document;
	while (ft_strchr(document_ptr, '$'))
	{
		varvalue = get_varvalue(ft_strchr(document_ptr, '$'));
		if (!varvalue)
			return (NULL); // ### TODO: エラー処理
		res = join_string_until_varvalue(res, &document_ptr);
		if (!res)
			return (NULL); // ### TODO: エラー処理
		res_tmp = ft_strjoin(res, varvalue);
		free(res);
		if (!res_tmp)
			return (NULL); // ### TODO: エラー処理
		res = res_tmp;
	}
	res = append_remainder(res, document_ptr);
	return (res);
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

static t_bool	expand_dquote(t_word_desc *desc)
{
	char	*rm_char;
	char	*res;

	rm_char = string_quote_removal(desc->word, DOUBLE_QUOTE_CHAR);
	if (!rm_char)
		return (FALSE);
	res = expand_string_to_string(rm_char);
	if (!res)
		return (free(rm_char), FALSE);
	free(desc->word);
	free(rm_char);
	desc->word = res;
	return (TRUE);
}

static t_bool	expand_var_token(t_word_list *list)
{
	t_bool	t;
	char	*res;

	while (list)
	{
		if (list->word->flag == W_SQUOTE)
			t = expand_squote(list->word);
		else if (list->word->flag == W_DQUOTE)
			t = expand_dquote(list->word);
		else if (is_hasdollar(list->word))
		{
			res = expand_string_to_string(list->word->word );
			if (!res)
				return (FALSE);
			free(list->word->word);
			list->word->word = res;
		}
		if (!t)
			return (FALSE);
		list = list->next;
	}
	return (TRUE);
}

t_bool	expand(t_command *command)
{
	while (command)
	{
		if (command->command)
		{
			if (!expand_var_token(command->command->words))
				return (FALSE);
		}
		command = command->next;
	}
	return (TRUE);
}