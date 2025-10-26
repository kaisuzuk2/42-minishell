/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:05:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/26 13:09:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

フラグを元に条件分岐する
1) $を展開する
2) クォートを除去する

チルダを展開する

*/

// expand_utils.c 
t_bool	is_hasdollar(t_word_desc *desc);
t_bool is_d_quote(t_word_desc *desc);
t_bool is_s_quote(t_word_desc *desc);


static char	*string_quote_removal(char *string, char quote)
{
	char	set[2];

	set[0] = quote;
	set[1] = '\0';
	return (ft_strtrim(string, set));
}

// envkey is alnum or underbar
static int	get_varlen(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (!(ft_isalnum(*str)) && !(*str == '_')) 
			break ;
		res++;
		str++;
	}
	return (res);
}

static char	*get_varvalue(t_varlist *env, char *doll_ptr)
{
	char	*varname;
	char	*varvalue;

	varvalue = NULL;
	varname = ft_substr(doll_ptr + 1, 0, get_varlen(doll_ptr + 1));
	if (!varname)
		return (NULL);
	varvalue = list_getenv(env, varname);
	free(varname);
	if (!varvalue)
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
		return (free(res), NULL);
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

t_bool expand(t_varlist *env, t_command *command)
{
	t_command *cur;

	cur = command;
	while (cur)
	{
		if (!cur->command || !expand_var_token(env, cur->command->words))
		{
			dispose_command(command);
			fatal_error("malloc", MALLOC_ERR_STR);
			exit(1);
		}
		cur = cur->next;
	}
	return (TRUE);
}