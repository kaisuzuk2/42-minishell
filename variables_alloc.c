/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:23:55 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/11 16:41:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_var	*create_shell_var(void)
{
	t_shell_var	*shell_variables;

	shell_variables = (t_shell_var *)xcalloc(sizeof(t_shell_var), 1);
	if (!shell_variables)
		return (NULL);
	return (shell_variables);
}

t_varlist	*create_varlist(void)
{
	t_varlist	*varlist;

	varlist = (t_varlist *)xcalloc(sizeof(t_varlist), 1);
	if (!varlist)
		return (NULL); 
	return (varlist);
}

char *create_exportstr(char *key, char *value)
{
	char *tmp;
	char *res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	if (!value)
		res = ft_strjoin(tmp, "");
	else
		res = ft_strjoin(tmp, value);
	free(tmp);
	if (!res)
		return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	return (res);
}