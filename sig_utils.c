/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:33:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 14:11:23 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_heredoc_hook(void)
{
	if (g_signal_state == SIGSTATE_INT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

int	signal_prompt_hook(void)
{
	if (g_signal_state == SIGSTATE_INT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

void	sigint_prompt_handler(int s)
{
	(void)s;
	g_signal_state = SIGSTATE_INT;
}

void	sigint_heredoc_handler(int s)
{
	(void)s;
	g_signal_state = SIGSTATE_INT;
}
