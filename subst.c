/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:09:16 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 14:10:26 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ifs_split(char const *s);

// envkey is alnum or underbar

static char	*join_string(char *res, char **document)
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

char	*expand_string_to_string(char *document, t_shell_env *shell_env)
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
		varvalue = get_varvalue(shell_env, ft_strchr(document_ptr, '$'));
		if (!varvalue)
			return (NULL);
		res = join_string(res, &document_ptr);
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

char	*expand_tilda(char *res, char **document, t_varlist *env)
{
	char	*home_value;
	char	*tmp;

	if ((*document)[0] == '~' && (((*document)[1] == '\0')
			|| ((*document)[1] == '/')))
	{
		home_value = list_getenv(env, "HOME");
		if (!home_value)
			return (ft_strdup(res));
		tmp = ft_strjoin(res, home_value);
		res = tmp;
		(*document)++;
		return (res);
	}
	return (ft_strdup(res));
}
