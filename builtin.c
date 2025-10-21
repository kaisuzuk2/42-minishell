/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:08 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/21 12:04:05 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool is_builtin(char *command)
{
	const char *builtin_name[] = {"cd", "echo", "env", "export", "pwd", "unset"};
	int i;

	i = 0;
	while (i < sizeof(builtin_name) / sizeof(*builtin_name))
	{
		if (!ft_strcmp(command, builtin_name[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_builtin_func *find_shell_builtin(const char *name)
{
	const char *builtin_name[] = {"cd", "echo", "env", "export", "pwd", "unset"};
	const t_builtin_func *builtin_table[] = {&builtin_cd, &builtin_echo, &builtin_env, &builtin_export, &builtin_pwd, &builtin_unset};
	int i;

	i = 0;
	while (i < sizeof(builtin_name) / sizeof(*builtin_name))
	{
		if (!ft_strcmp(name, builtin_name[i]))
			return (builtin_table[i]);
		i++;
	}
	return (NULL);
}

int execute_builtin_command(t_command *cmd, t_varlist *env)
{
	char *command;
	t_word_list *arg;	
	t_builtin_func *f;

	command = cmd->words->word->word;
	f = NULL;
	f = find_shell_builtin(command);
	if (!f)
		return (99); // ### TODO: エラー処理
	arg = cmd->words->next;
	return (f(arg, env));
}