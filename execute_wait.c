/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:12:17 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 11:12:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_signal_end(int last_status)
{
	if (last_status == SIGINT)
		ft_dprintf(STDOUT_FILENO, "\n");
}

static void	print_core_dumped(int last_status)
{
	if (last_status == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
}

static pid_t	status_to_exitcode(int last_status)
{
	if (WIFSIGNALED(last_status))
		return (print_core_dumped(WTERMSIG(last_status)), 128
			+ WTERMSIG(last_status));
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else
		return (EXECUTION_FAILURE);
}

pid_t	wait_for(pid_t lastpid)
{
	int		status;
	int		last_status;
	pid_t	wpid;
	t_bool	sig_flg;

	sig_flg = FALSE;
	last_status = -1;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
			break ;
		if (!sig_flg && WIFSIGNALED(status))
		{
			print_signal_end(WTERMSIG(status));
			sig_flg = TRUE;
		}
		if (wpid == lastpid)
			last_status = status;
	}
	if (lastpid < 0)
		return (EXECUTION_FAILURE);
	return (status_to_exitcode(last_status));
}