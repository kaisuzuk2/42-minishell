/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:53:00 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/27 12:25:19 by kaisuzuk         ###   ########.fr       */
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


// ### TODO: 失敗して-1返すのはmalloc時のみにする
int	ft_mkstemp(char **template)
{
	int		i;
	char	*filename;
	char	*addnum;

	i = 0;
	while (i < 100)
	{
		addnum = ft_itoa(i);
		if (!addnum)
			return (-1);
		filename = ft_strjoin(*template, addnum);
		if (!filename)
			return (free(addnum), -1);
		if (is_noexist(filename))
		{
			*template = filename;
			return (open(filename, O_RDWR | O_CREAT | O_EXCL, 0600));
		}
		free(addnum);
		free(filename);
		i++;
	}
	free(*template);
	*template = NULL;
	return (-1);
}