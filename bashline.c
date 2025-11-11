/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:21:40 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/11 12:11:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: readlineの設定を考える
// https://tiswww.case.edu/php/chet/readline/readline.html

static void interactive_readline(void)
{
	rl_instream = stdin;
	rl_outstream = stderr;
}

static void non_interactive_readline(void)
{
	int null_fd;

	rl_instream = stdin;
	null_fd = open("/dev/null", O_WRONLY);
	if (null_fd < 0)
	{
		sys_error("open");
		exit(EX_FATAL_ERROR);
	}
	if (dup2(null_fd, STDERR_FILENO) < 0)
	{
		sys_error("dup2");
		exit(EX_FATAL_ERROR);
	}
	close(null_fd);
	rl_outstream = stderr;
}

void initialize_readline(void)
{
	// if (isatty(STDIN_FILENO))
		interactive_readline();
	// else
	// 	non_interactive_readline();
}