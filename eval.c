/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:21:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/09/12 11:38:33 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

reader_loop 
1) Read one command unit (this may span multiple lines, not just a single line).
2) Parse it into a command tree using the lexer and parser.
3) Execute the command (built-ins directly, or external commands via fork/exec, pipelines, etc.).
4) Clean up after execution (free structures, reset state).
5) Repeat until EOF (or an exit/error condition breaks the loop).

*/

/*

read_command
Preparation function for reading the command line.

*/

/*
parse_command 
Trap handling and displaying the PROMPT_COMMAND environment variable
*/
// ひとまずここで読み取った１行をトークン化して、リストにする


/*

lexer rule 
https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03

*/

static t_word_list parse_command(char *line)
{
	
}

static char *read_command(void)
{
	return (parse_command());
}

int reader_loop(void)
{
	while (1)
	{
		line = readline("minishell $");
		if (line == NULL)
			break;
		if (*line)
			add_history(line);
		execute_command(line, envp);
		free(line);	
	}
	return (0)
}