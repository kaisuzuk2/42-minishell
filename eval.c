/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:21:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/09/11 11:00:20 by kaisuzuk         ###   ########.fr       */
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


static char *parse_command()
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
		
	}
}