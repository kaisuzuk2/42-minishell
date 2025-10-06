/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:21:40 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/06 13:31:48 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: readlineの設定を考える
// https://tiswww.case.edu/php/chet/readline/readline.html
void initialize_readline(void)
{
	rl_instream = stdin;
	rl_outstream = stderr;
}