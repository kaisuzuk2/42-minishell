/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 08:57:40 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/06 09:13:32 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

#include <signal.h>

typedef enum e_signal_state
{
	SIGSTATE_NONE,
	SIGSTATE_INT, 
	SIGSTATE_QUIT, 

} t_signal_state;

extern volatile sig_atomic_t g_signal_state;

#endif