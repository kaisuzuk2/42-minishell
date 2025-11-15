/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:12:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 11:15:11 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_isdir(char *command);

static int	shell_execve(char *command, char **arg, char **env)
{
	int	i;
	int	status;

	execve(command, arg, env);
	i = errno;
	if (i != ENOEXEC)
	{
		if (file_isdir(command) && ft_strcmp(command, ".."))
			fatal_error(command, "Is a directory");
		else if (i == ENOENT || !ft_strcmp(command, ".."))
		{
			free(command);
			dispose_char_arr(arg);
			dispose_char_arr(env);
			return (fatal_error(command, NOTFOUND_STR), EX_NOTFOUND);
		}
		else
			internal_error(command, strerror(i));
	}
	else
		fatal_error(command, "cannnot support");
	free(command);
	dispose_char_arr(arg);
	dispose_char_arr(env);
	return (EX_NOEXEC);
}

int	execute_disk_command(t_command *cmd, t_pipefd pipefd,
		t_shell_env *shell_env)
{
	char	*command;
	char	**arg;
	char	**envarr;

	if (cmd->command->redirects && do_redirections(cmd->command->redirects,
			shell_env) != 0)
		return (EXECUTION_FAILURE);
	if (!cmd->command->words)
		return (EXECUTION_SUCCESS);
	if (is_builtin(cmd->command->words->word->word))
		return (execute_builtin_command(cmd, pipefd, shell_env));
	if (!search_for_command(cmd->command->words->word->word, shell_env->env,
			&command))
		return (fatal_error(cmd->command->words->word->word, NOTFOUND_STR),
			EX_NOTFOUND);
	arg = strvec_from_word_list(cmd->command->words);
	envarr = get_env_arr(shell_env->env);
	if (!command || !envarr || !arg)
		return (free(command), dispose_char_arr(envarr), dispose_char_arr(arg),
			fatal_error("malloc", MALLOC_ERR_STR), EX_FATAL_ERROR);
	if (!update_key_value(shell_env->env, "_", command, 1))
		return (free(command), EX_FATAL_ERROR);
	return (shell_execve(command, arg, envarr));
}