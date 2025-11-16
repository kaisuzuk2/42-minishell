/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:53:00 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 11:39:52 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_noexist(char *filename)
{
	const int	res = access(filename, F_OK);

	if (res == 0)
		return (FALSE);
	return (TRUE);
}

int	ft_mkstemp(char **template)
{
	int		i;
	char	*filename;
	char	*addnum;

	i = 0;
	while (i < 100)
	{
		addnum = ft_itoa(i++);
		if (!addnum)
			return (fatal_error("malloc", MALLOC_ERR_STR), EXECUTION_MEMERR);
		filename = ft_strjoin(*template, addnum);
		if (!filename)
			return (fatal_error("malloc", MALLOC_ERR_STR), free(addnum),
				EXECUTION_MEMERR);
		if (is_noexist(filename))
		{
			*template = filename;
			return (open(filename, O_RDWR | O_CREAT | O_EXCL, 0600));
		}
		free(addnum);
		free(filename);
	}
	free(*template);
	*template = NULL;
	return (fatal_error("ft_mkstemp", MKSTEMP_ERR), EXECUTION_ERR);
}
