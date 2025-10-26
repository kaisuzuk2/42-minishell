/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:09:16 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/26 13:12:18 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


char	*expand_string_to_string(t_varlist *env, char *document)
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
		varvalue = get_varvalue(env, ft_strchr(document_ptr, '$'));
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