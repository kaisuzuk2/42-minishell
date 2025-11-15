/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:10:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 09:08:05 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_state = SIGSTATE_NONE;

void	set_handler(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	sigaction(sig, &sa, NULL);
}

static void	sigint_prompt_handler(int s)
{
	(void)s;
	g_signal_state = SIGSTATE_INT;
}

static void sigint_heredoc_handler(int s)
{
	(void)s;
	g_signal_state = SIGSTATE_INT;
}

int signal_heredoc_hook(void)
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

void	enter_prompt_mode(void)
{
	// rl_catch_signals = 0;
	// rl_event_hook = signal_prompt_hook;
	if (isatty(STDIN_FILENO))
		rl_event_hook = signal_prompt_hook;
	set_handler(SIGINT, sigint_prompt_handler, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}

void enter_heredoc_mode(void)
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

void set_signal_for_parent(void)
{
	set_handler(SIGINT, SIG_IGN, 0);
	set_handler(SIGQUIT, SIG_IGN, 0);
}