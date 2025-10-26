/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:08 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/26 18:25:58 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin_func	*find_builtin_func(const char *name,
		const char *builtin_list[], const t_builtin_func builtin_table[])
{
	int	i;

	i = 0;
	while (i < sizeof(builtin_list) / sizeof(*builtin_list))
	{
		if (!ft_strcmp(name, builtin_list[i]))
			return (builtin_table[i]);
		i++;
	}
	return (NULL);
}

t_bool	is_builtin(char *command, const char *builtin_list[])
{
	int	i;

	i = 0;
	while (i < sizeof(builtin_list) / sizeof(*builtin_list))
	{
		if (!ft_strcmp(command, builtin_list[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	execute_builtin_command(t_command *cmd, const char *builtin_list[],
		const t_builtin_func builtin_table[], t_varlist *env)
{
	char *command;
	t_word_list *arg;
	t_builtin_func *f;

	command = cmd->words->word->word;
	f = NULL;
	f = find_builtin_func(command, builtin_list, builtin_table);
	if (!f)
		return (99); // ### TODO: エラー処理
	arg = cmd->words->next;
	return ((*f)(arg, env));
}