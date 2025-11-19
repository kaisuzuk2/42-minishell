/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 08:57:40 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 12:19:51 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>

typedef enum e_signal_state
{
	SIGSTATE_NONE,
	SIGSTATE_INT,
	SIGSTATE_QUIT,
}								t_signal_state;

extern volatile sig_atomic_t	g_signal_state;

// sig.c
void	set_signal_for_parent(void);
void	reset_signals_for_child(void);
void	enter_heredoc_mode(void);
void	enter_prompt_mode(void);

#endif