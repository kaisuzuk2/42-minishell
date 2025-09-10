/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:58:01 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/09/10 17:24:15 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *savestring(const char *str)
{
	char *res;
	
	res = ft_strdup(str);
	return (res);
}

static int is_absolute_path(char *filename)
{
	return (ft_strchr(filename, '/'));
}

// ACCESS and EXECUTABLE OK		:	1
// NOT EXIST or NOT EXECUTABLE	:	0
static int file_status(char *command_path)
{
	if (!access(command_path, F_OK))
	{
		if (!access(command_path, X_OK))
			return (1);
		else
			return (0);
	}
	return (0);
}

/*
TODO: 
1) getenv or environ or envp
*/
// MALLOC ERROR : savestring->filename
// SUCCESS 		: char ptr
char *search_for_command(const char *filename)
{
	char *path_line;
	char **path_list;
	int i;
	char *tmp;
	char *res;

	path_line = getenv("PATH");
	if (is_absolute_path(filename))
		return (savestring(filename));
	if (path_line == NULL)
		return (savestring(filename));
	path_list = ft_split(path_line, ':');
	if (!path_list)
		return (savestring(filename));
	i = 0;
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		if (!tmp)
			return (savestring(filename));
		res = ft_strjoin(tmp, filename);
		if (!res)
			return (savestring(filename));
		free(tmp);
		if (file_status(res))
			return (res);
		else
			free(res);
		i++;
	}
	return (savestring);
}