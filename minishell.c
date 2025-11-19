/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:13:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 14:32:22 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	initialize_readline(void)
{
	rl_instream = stdin;
	rl_outstream = stderr;
}

static char	*read_command(t_shell_env *shell_env)
{
	int		last_status;
	char	*line;

	line = readline(PS1);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			ft_dprintf(STDERR_FILENO, "exit\n");
		return (NULL);
	}
	if (g_signal_state == SIGSTATE_INT)
	{
		set_last_status(130, shell_env);
		return (NULL);
	}
	return (line);
}

static int	is_signal(t_shell_env *shell_env)
{
	if (g_signal_state == SIGSTATE_INT)
	{
		set_last_status(130, shell_env);
		g_signal_state = SIGSTATE_NONE;
		return (TRUE);
	}
	return (FALSE);
}

static int	reader_loop(t_shell_env *shell_env)
{
	char			*line;
	t_token_list	*token;
	t_command		*parse;

	while (1)
	{
		line = read_command(shell_env);
		if (!line)
		{
			if (is_signal(shell_env))
				continue ;
			return (shell_env->last_status);
		}
		if (*line)
			add_history(line);
		token = tokenize(line, shell_env);
		if (!token)
			continue ;
		parse = parser(token, shell_env);
		if (!parse)
			continue ;
		expand(parse, shell_env);
		set_last_status(execute_pipeline(parse, shell_env), shell_env);
		dispose_command(parse);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_shell_env	*shell_env;
	int			last_status;

	(void)argc;
	(void)argv;
	shell_env = initialize_shell_variables(envp);
	if (!shell_env)
		exit(EX_FATAL_ERROR);
	enter_prompt_mode();
	initialize_readline();
	last_status = reader_loop(shell_env);
	dispose_env(shell_env);
	return (last_status);
}
