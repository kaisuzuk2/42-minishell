/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:13:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/16 12:42:18 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tmp code ↓

#include <stdio.h>
#include <sys/types.h>
#include <limits.h>
#include <bsd/string.h>
#include "minishell.h"

void fatal_error(const char *msg)  __attribute__((noreturn));

void fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "fatal Error: %s\n", msg);
	exit(1);
}


char *search_path(const char *filename)
{
	char path[PATH_MAX];
	char *value;
	char *end;

	value = getenv("PATH");
	while (*value)
	{
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			strlcpy(path, value, PATH_MAX);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			char *dup;

			dup = strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}


int interpret(char *line)
{
	extern char **environ;
	char *argv[] = {search_path(line), NULL};
	pid_t pid;
	int wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		execve(search_path(line), argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

void show_token_and_redir(t_command *command)
{
	t_word_list *list;
	t_redirect *redir;

	list = command->words;
	while (list)
	{
		printf("command %s : ", list->word->word);
		list = list->next;
	}
	printf("\n");
	redir = command->redirects;
	while (redir)
	{
		printf("redirect %d - %s :", redir->redirector.dest, redir->redirectee.filename->word);
		redir = redir->next;
	}
	printf("\n");
}

void show_parse_list(t_command *command)
{
	if (command)
	{
		show_token_and_redir(command->command);
		command = command->next;
	}
}
// tmp code ↑

/*
parse test
*/
// int main(void)
// {
// 	char *line;

// 	t_token_list *token;
// 	t_command *parse;

// 	while (1)
// 	{
// 		//### TODO:  prompt is $PS1
// 		line = readline("minishell$ ");

// 		if (!line)
// 			break;
// 		if (*line)
// 			add_history(line);
// 		token = tokenize(line);
// 		// show_token_list(token);
// 		parse = parser(token);
// 		dispose_token_words(token);
// 		expand(parse);
// 		show_parse_list(parse);
// 		// interpret(line);
// 		dispose_command(parse);
// 		free(line);
// 	}
// }

int main(void)
{
	char *line;

	t_token_list *token;
	t_command *parse;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		token = tokenize(line);
		parse = parser(token);
		expand(parse);
		execute_pipeline(parse);
	}
}