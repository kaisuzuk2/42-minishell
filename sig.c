/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:10:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 15:06:06 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_state = SIGSTATE_NONE;

void				sigint_heredoc_handler(int s);
void				sigint_prompt_handler(int s);
int					signal_prompt_hook(void);
int					signal_heredoc_hook(void);

static void	set_handler(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	sigaction(sig, &sa, NULL);
}

void	enter_prompt_mode(void)
{
	if (isatty(STDIN_FILENO))
		rl_event_hook = signal_prompt_hook;
	set_handler(SIGINT, sigint_prompt_handler, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}

void	enter_heredoc_mode(void)
{
	rl_event_hook = signal_heredoc_hook;
	rl_catch_signals = 0;
	set_handler(SIGINT, sigint_heredoc_handler, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}

void	reset_signals_for_child(void)
{
	set_handler(SIGINT, SIG_DFL, 0);
	set_handler(SIGQUIT, SIG_DFL, 0);
}

void	set_signal_for_parent(void)
{
	set_handler(SIGINT, SIG_IGN, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}
