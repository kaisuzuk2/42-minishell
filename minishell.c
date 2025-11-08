/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:13:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/08 14:58:51 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tmp code ↓

#include "minishell.h"
#include <bsd/string.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>

char	*minishell_input(char *readline_input);

// void fatal_error(const char *msg)  __attribute__((noreturn));

// void fatal_error(const char *msg)
// {
// 	dprintf(STDERR_FILENO, "fatal Error: %s\n", msg);
// 	exit(1);
// }

// char *search_path(const char *filename)
// {
// 	char path[PATH_MAX];
// 	char *value;
// 	char *end;

// 	value = getenv("PATH");
// 	while (*value)
// 	{
// 		bzero(path, PATH_MAX);
// 		end = strchr(value, ':');
// 		if (end)
// 			strncpy(path, value, end - value);
// 		else
// 			strlcpy(path, value, PATH_MAX);
// 		strlcat(path, "/", PATH_MAX);
// 		strlcat(path, filename, PATH_MAX);
// 		if (access(path, X_OK) == 0)
// 		{
// 			char *dup;

// 			dup = strdup(path);
// 			if (dup == NULL)
// 				fatal_error("strdup");
// 			return (dup);
// 		}
// 		if (end == NULL)
// 			return (NULL);
// 		value = end + 1;
// 	}
// 	return (NULL);
// }

// int interpret(char *line)
// {
// 	extern char **environ;
// 	char *argv[] = {search_path(line), NULL};
// 	pid_t pid;
// 	int wstatus;

// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		execve(search_path(line), argv, environ);
// 		fatal_error("execve");
// 	}
// 	else
// 	{
// 		wait(&wstatus);
// 		return (WEXITSTATUS(wstatus));
// 	}
// }

void	show_token_and_redir(t_command *command)
{
	t_word_list	*list;
	t_redirect	*redir;

	if (!command)
		return ;
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
		printf("redirect %d - %s :", redir->redirector.dest,
			redir->redirectee.filename->word);
		redir = redir->next;
	}
	printf("\n");
}

void	show_parse_list(t_command *command)
{
	while (command)
	{
		show_token_and_redir(command->command);
		command = command->next;
	}
}

void	show_envvalue(t_varlist *list)
{
	while (list->next)
	{
		printf("%s=%s\n", list->var->name, list->var->value);
		list = list->next;
	}
}

void	show_token_list(t_token_list *token)
{
	if (token == NULL)
		return ;
	while (token->word->kind != TK_EOF)
	{
		printf("%s\n", token->word->word);
		token = token->next;
	}
}
// tmp code ↑

/*
parse test
*/
// int main(int argc, char *argv[], char *envp[])
// {
// 	char *line;

// 	t_token_list *token;
// 	t_command *parse;
// 	t_varlist *env;

// 	env = initialize_shell_variables(envp);
// 	parse = NULL;
// 	token = NULL;
// 	while (1)
// 	{
// 		//### TODO:  prompt is $PS1
// 		line = readline("minishell$ ");

// 		if (!line)
// 			break ;
// 		if (*line)
// 			add_history(line);
// 		token = tokenize(line);
// 		if (!token)
// 			continue ;
// 		show_token_list(token);
// 		// dispose_token_words(token);
// 		parse = parser(token);
// 		if (!parse)
// 			continue ;
// 		dispose_token_words(token);
// 		expand(env, parse);
// 		show_parse_list(parse);
// 		// interpret(line);
// 		dispose_command(parse);
// 		free(line);
// 	}
// 	dispose_token_words(token);
// 	dispose_command(parse);
// }

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_token_list	*token;
	t_command		*parse;
	t_shell_env		*shell_variables;
	char			*input;

	enter_prompt_mode();
	shell_variables = initialize_shell_variables(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_dprintf(STDOUT_FILENO, "exit\n");
			dispose_env(shell_variables);
			break ;
		}
		if (*line == '\0' && g_signal_state == SIGSTATE_INT)
		{
			set_last_status(130, shell_variables);
			g_signal_state = SIGSTATE_NONE;
			continue ;
		}
		if (*line)
			add_history(line);
		token = tokenize(line, shell_variables);
		if (!token)
			continue ;
		parse = parser(token, shell_variables);
		if (!parse)
			continue ;
		expand(parse, shell_variables);
		// show_envvalue(shell_variables);
		set_last_status(execute_pipeline(parse, shell_variables),
			shell_variables);
		dispose_command(parse);
	}
	return (0);
}
