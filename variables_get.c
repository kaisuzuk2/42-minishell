/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:21:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 15:22:12 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char *env)
{
	char	*res;
	int		i;

	if (!ft_strchr(env, '='))
		return (savestring(env));
	res = savestring(env);
	if (!res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		if (res[i] == '=' || res[i] == '+')
			break ;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_env_value(char *env)
{
	char	*res;
	int		i;
	char	*value_ptr;

	value_ptr = ft_strchr(env, '=');
	if (!value_ptr)
		res = ft_strdup("");
	else
		res = savestring(++value_ptr);
	if (!res)
		return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	return (res);
}