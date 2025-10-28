/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:23:55 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 18:35:11 by kaisuzuk         ###   ########.fr       */
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
