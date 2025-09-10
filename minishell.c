/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:31:35 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/09/10 17:01:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1) getline loop
2) parse 
3) exec
*/

static void initialize_readline(void)
{
	rl_instream = stdin;
	rl_outstream = stderr;
}

int main(int argc, char *argv[], char **envp)
{
	char *line;

	initialize_readline();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (*line)
			add_history(line);
		execute_command(line, envp);
		free(line);
	}
	return (0);
}