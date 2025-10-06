/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:13:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/06 13:49:34 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tmp code ↓

#include <stdio.h>
#include <sys/types.h>

void fatal_error(const char *msg)  __attribute__((noreturn));

void fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "fatal Error: %s\n", msg);
	exit(1);
}

int interpret(char *line)
{
	extern char **environ;
	char *argv[] = {line, NULL};
	pid_t pid;
	int wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		execve(line, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

// tmp code ↑

int main(void)
{
	char *line;
	
	while (1)
	{
		//TODO:  prompt is $PS1
		line = readline("minishell$ ");

		if (!line)
			break;
		if (*line)
			add_history(line);
		interpret(line);
		free(line);
	}
}