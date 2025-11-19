/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:29:59 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 11:05:20 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// findcmd_utils_bonus.c
t_bool			is_absolute_program(char *arg);

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

static t_bool	file_status(char **full_path, char **file_to_lose_on)
{
	if (!access(*full_path, F_OK))
	{
		if (file_isdir(*full_path))
			return (FALSE);
		if (!access(*full_path, X_OK))
			return (TRUE);
		else
		{
			if (!*file_to_lose_on)
				*file_to_lose_on = savestring(*full_path);
			if (!*file_to_lose_on)
				return (FALSE);
			return (FALSE);
		}
	}
	return (FALSE);
}

static t_bool	find_user_command_in_path(char **full_path, char *cmd,
		char **path_list, char **file_to_lose_on)
{
	int	i;

	i = 0;
	while (path_list[i])
	{
		*full_path = join_path_element(path_list[i], cmd);
		if (!*full_path)
			return (fatal_error("malloc", MALLOC_ERR_STR), FALSE);
		if (file_status(full_path, file_to_lose_on))
			break ;
		else
		{
			free(*full_path);
			*full_path = NULL;
		}
		i++;
	}
	return (TRUE);
}

t_bool	search_for_command(char *cmd, t_varlist *env, char **command)
{
	char	**path_list;
	char	*path;
	char	*full_path;
	char	*file_to_lose_on;

	if (is_absolute_program(cmd) || !*cmd)
		return (*command = savestring(cmd), TRUE);
	path = get_listenv(env, "PATH");
	if (!path)
		return (*command = savestring(cmd), TRUE);
	path_list = ft_split(path, ':');
	if (!path_list)
		return (*command = NULL, FALSE);
	file_to_lose_on = NULL;
	full_path = NULL;
	if (!find_user_command_in_path(&full_path, cmd, path_list,
			&file_to_lose_on))
		return (dispose_char_arr(path_list), *command = NULL, FALSE);
	dispose_char_arr(path_list);
	if (full_path)
		return (free(file_to_lose_on), *command = full_path, TRUE);
	if (file_to_lose_on)
		return (*command = file_to_lose_on, TRUE);
	return (*command = NULL, FALSE);
}
