/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:08 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/27 15:39:23 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin_func	*find_builtin_func(const char *name,
		const t_builtin *builtin_table, const size_t table_size)
{
	int	i;

	i = 0;
	while (i < table_size)
	{
		if (!ft_strcmp(name, builtin_table[i].name))
			return (builtin_table[i].f);
		i++;
	}
	return (NULL);
}

t_bool	is_builtin(char *command, const t_builtin *builtin_table, const size_t table_size)
{
	int	i;

	i = 0;
	while (i < table_size)
	{
		if (!ft_strcmp(command, builtin_table[i].name))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	execute_builtin_command(t_command *cmd, const t_builtin *builtin_table,
		const size_t table_size, t_varlist *env)
{
	char *command;
	t_word_list *arg;
	t_builtin_func *f;

	command = cmd->command->words->word->word;
	f = NULL;
	f = find_builtin_func(command, builtin_table, table_size);
	if (!f)
		return (internal_error(BUILTIN_ERR_STR, command), EXECUTION_FAILURE);
	arg = cmd->command->words->next;
	return ((*f)(arg, env));
}

t_builtin_table get_builtin_table(void)
{
	t_builtin_table info;
	static const t_builtin builtin_table[] = {
		{"cd", builtin_cd},
		{"echo", builtin_echo},
		{"env", builtin_env},
		{"export", builtin_export},
		{"pwd", builtin_pwd},
		{"unset", builtin_unset},
	};

	info.table = builtin_table;
	info.size = sizeof(builtin_table) / sizeof(builtin_table[0]);
	return (info);

}