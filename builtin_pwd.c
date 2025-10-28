/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:56:10 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 11:38:03 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool is_same_file(const char *path1, const char *path2, struct stat *stp1, struct stat *stp2)
{
	struct stat st1;
	struct stat st2;

	if (!stp1)
	{
		if (stat(path1, &st1))
			return (0);
		stp1 = &st1;
	}
	if (!stp2)
	{
		if (stat(path2, &st2))
			return (0);
		stp2 = &st2;
	}
	return ((stp1->st_dev == stp2->st_dev) && (stp1->st_ino == stp2->st_ino));
}

// int builtin_pwd(t_word_list *list, t_varlist *env)
// {
// 	char *directory;

// 	directory = list_getenv(env, "PWD");
// 	if (!directory)
// 	{
// 		directory = getcwd(NULL, 0);
// 		if (!directory)
// 			return (sys_error("pwd failed"), EXECUTION_FAILURE);
// 		ft_dprintf(STDOUT_FILENO, "%s\n", directory);
// 		return (EXECUTION_SUCCESS);
// 	}
// 	if (!is_same_file(".", directory, (struct stat *)0, (struct stat *)0))
// 	{
// 		directory = getcwd(NULL, 0);
// 		if (!directory)
// 			return (sys_error("pwd failed"), EXECUTION_FAILURE);
// 		ft_dprintf(STDOUT_FILENO, "%s\n", directory);
// 		return (EXECUTION_SUCCESS);
// 	}
// 	ft_dprintf(STDOUT_FILENO, "%s\n", directory);
// 	return (EXECUTION_SUCCESS);
// }

int builtin_pwd(t_word_list *list, t_varlist *env)
{
	char *directory;

	directory = list_getenv(env, "PWD");
	if (!directory || !is_same_file(".", directory, (struct stat *)0, (struct stat *)0))
	{
		directory = getcwd(NULL, 0);
		if (!directory)
			return (sys_error("pwd failed"), EXECUTION_FAILURE);
		ft_dprintf(STDOUT_FILENO, "%s\n", directory);
		return (EXECUTION_SUCCESS);
	}
	ft_dprintf(STDOUT_FILENO, "%s\n", directory);
	return (EXECUTION_SUCCESS);
}