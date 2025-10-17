/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:29:59 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/17 12:51:22 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// findcmd_utils_bonus.c
t_bool			is_absolute_program(char *arg);
void			free_path(char **path);

static char	*join_path_element(char *dir, char *arg)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, arg);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

static t_bool	file_status(char *full_path, char **file_to_lose_on)
{
	if (!access(full_path, F_OK))
	{
		if (!access(full_path, X_OK))
			return (TRUE);
		else
		{
			if (!*file_to_lose_on)
				*file_to_lose_on = savestring(full_path);
			if (!*file_to_lose_on)
			{
				return (FALSE); // ### TODO: エラー処理
			}
			return (FALSE);
		}
	}
	return (FALSE);
}

static char	*find_user_command_in_path(char *cmd, char **path_list,
		char **file_to_lose_on)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		full_path = join_path_element(path_list[i], cmd);
		if (!full_path)
		{
			return (NULL); // ### TODO: エラー処理
		}
		if (file_status(full_path, file_to_lose_on))
			break ;
		else
		{
			free(full_path);
			full_path = NULL;
		}
		i++;
	}
	return (full_path);
}

char	*search_for_command(char *cmd)
{
	char	**path_list;
	char	*path;
	char	*full_path;
	char	*file_to_lose_on;

	if (is_absolute_program(cmd))
		return (savestring(cmd));
	path = getenv("PATH");
	if (!path)
		return (savestring(cmd));
	path_list = ft_split(path, ':');
	if (!path_list)
	{
		return (NULL); //### TODO: エラー処理
	}
	file_to_lose_on = NULL;
	full_path = find_user_command_in_path(cmd, path_list, &file_to_lose_on);
	free_path(path_list);
	if (full_path)
		return (free(file_to_lose_on), full_path);
	if (file_to_lose_on)
		return (file_to_lose_on);
	return (NULL);
}