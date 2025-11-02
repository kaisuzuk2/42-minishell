/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:09:16 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/02 11:38:26 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// envkey is alnum or underbar
static t_bool	is_special_parameters(char c)
{
	const char	*special_parameters = "?";

	return (ft_strchr(special_parameters, c) != 0);
}

char	*get_special_value(t_shell_env *shell_env, char *s)
{
	char	*res;

	if (s[0] == '?' && s[1] == '\0')
		return (ft_itoa(get_last_status(shell_env)));
	return (ft_strdup(""));
}

static int	get_varlen(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (is_special_parameters(*str))
			return (1);
		if (!(ft_isalnum(*str)) && !(*str == '_'))
			break ;
		res++;
		str++;
	}
	return (res);
}

static char	*get_varvalue(t_shell_env *shell_env, char *doll_ptr)
{
	char	*varname;
	char	*varvalue;

	varvalue = NULL;
	varname = ft_substr(doll_ptr + 1, 0, get_varlen(doll_ptr + 1));
	if (!varname)
		return (NULL);
	if (is_special_parameters(*varname))
		varvalue = get_special_value(shell_env, varname);
	else
		varvalue = list_getenv(shell_env->env, varname);
	free(varname);
	if (!varvalue)
		return (ft_strdup(""));
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

static char	*join_string_until_varvalue_and_quote(char *res, char **document)
{
	char	*doll_ptr;
	char	*tmp;
	char	*res_tmp;
	int i;

	i = 0;
	while ((*document)[i] && (*document)[i] != '$' && (*document)[i] != '\'' && (*document)[i] != '\"')
		i++;
	tmp = ft_substr(*document, 0, i);
	if (!tmp)
		return (free(res), NULL);
	res_tmp = ft_strjoin(res, tmp);
	free(res);
	free(tmp);
	*document = &(*document)[i];
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

char	*expand_string_to_string(char *document, t_shell_env *shell_env)
{
	char *res;
	char *res_tmp;
	char *document_ptr;
	char *varvalue;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	document_ptr = document;
	while (ft_strchr(document_ptr, '$'))
	{
		varvalue = get_varvalue(shell_env, ft_strchr(document_ptr, '$'));
		if (!varvalue)
			return (NULL);
		res = join_string_until_varvalue(res, &document_ptr);
		if (!res)
			return (NULL);
		res_tmp = ft_strjoin(res, varvalue);
		free(res);
		if (!res_tmp)
			return (NULL);
		res = res_tmp;
	}
	res = append_remainder(res, document_ptr);
	return (free(document), res);
}

static char *expand_quote_and_value(char **document_p, char *document, char c, t_shell_env *shell_env)
{
	int i;
	char *trim;
	char *tmp;
	char *doc;
	char *val;

	i = 1;
	while (document[i] != c)
		i++;
	i++;
	tmp = ft_substr(document, 0, i);
	*document_p = &document[i];
	trim = string_quote_removal(tmp, c);
	if (c == '\"' && ft_strchr(trim, '$'))
	{
		i = 0;
		while (trim[i] != '$')
			i++;
		doc = ft_substr(trim, 0, i);
		val =  get_varvalue(shell_env, &trim[i]);
		return (ft_strjoin(doc, val));		
	}
	return (trim);
}

char *expand_string_width_quote(char *document, t_shell_env *shell_env)
{
	char *res;
	int i;
	int varlen;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (*document)
	{
		if (*document == '\'')
		{
			res = ft_strjoin(res, expand_quote_and_value(&document, document, '\'', shell_env));
		}
		else if (*document == '\"')
		{
			res = ft_strjoin(res, expand_quote_and_value(&document, document, '\"', shell_env));
		}
		else if (*document == '$')
		{
			varlen = get_varlen(document);
			res = get_varvalue(shell_env, &document[1]);
		}
		else
			res = join_string_until_varvalue_and_quote(res, &document);
	}
	return (res);
}