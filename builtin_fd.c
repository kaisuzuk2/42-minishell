/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:11:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 12:11:43 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_bool	save_stdfd(int *fd_arr)
{
	int	i;

	fd_arr[STDIN_FILENO] = dup(STDIN_FILENO);
	fd_arr[STDOUT_FILENO] = dup(STDOUT_FILENO);
	fd_arr[STDERR_FILENO] = dup(STDERR_FILENO);
	i = 0;
	while (i < STDFD_SIZE)
	{
		if (fd_arr[i] < 0)
			return (sys_error("dup2 failed"), FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	reset_stdfd(int *fd_arr)
{
	if (dup2(fd_arr[STDIN_FILENO], STDIN_FILENO) < 0)
		return (sys_error("dup2 failed"), FALSE);
	if (dup2(fd_arr[STDOUT_FILENO], STDOUT_FILENO) < 0)
		return (sys_error("dup2 failed"), FALSE);
	if (dup2(fd_arr[STDERR_FILENO], STDERR_FILENO) < 0)
		return (sys_error("dup2 failed"), FALSE);
	return (TRUE);
}

void	close_stdfd(int *fd_arr)
{
	int	i;

	i = 0;
	while (i < STDFD_SIZE)
	{
		close(fd_arr[i]);
		i++;
	}
}