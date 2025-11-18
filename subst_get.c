/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:57:58 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 10:20:51 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_varlen(char *str)
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

char	*get_varvalue(t_shell_env *shell_env, char *doll_ptr)
{
	char	*varname;
	char	*varvalue;
	char	*tmp_varvalue;

	varvalue = NULL;
	varname = ft_substr(doll_ptr + 1, 0, get_varlen(doll_ptr + 1));
	if (!varname)
		return (NULL);
	if (is_special_parameters(*varname))
		varvalue = get_special_value(shell_env, varname);
	else
	{
		tmp_varvalue = get_listenv(shell_env->env, varname);
		if (!tmp_varvalue)
			varvalue = ft_strdup("");
		else
			varvalue = savestring(tmp_varvalue);
	}
	free(varname);
	return (varvalue);
}
