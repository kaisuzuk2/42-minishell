/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:08 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 12:15:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin_fd.c
t_bool					save_stdfd(int *fd_arr);
t_bool					reset_stdfd(int *fd_arr);
void					close_stdfd(int *fd_arr);

static t_builtin_func	*get_builtin_func(const char *name)
{
	int				i;
	t_builtin_table	info;

	info = get_builtin_table();
	i = 0;
	while (i < info.size)
	{
		if (!ft_strcmp(name, info.table[i].name))
			return (info.table[i].f);
		i++;
	}
	return (NULL);
}

t_builtin_table	get_builtin_table(void)
{
	t_builtin_table			info;
	static const t_builtin	builtin_table[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{"export", builtin_export},
	{"pwd", builtin_pwd},
	{"unset", builtin_unset},
	};

	info.table = builtin_table;
	info.size = sizeof(builtin_table) / sizeof(builtin_table[0]);
	return (info);
}

t_bool	is_builtin(char *command)
{
	int				i;
	t_builtin_table	builtin_info;

	builtin_info = get_builtin_table();
	i = 0;
	while (i < builtin_info.size)
	{
		if (!ft_strcmp(command, builtin_info.table[i].name))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static int	handle_exit_command(t_command *cmd, t_shell_env *shell_env,
		int status)
{
	if (status > 255)
		return (EXIT_FAILURE);
	dispose_command(cmd->head);
	dispose_env(shell_env);
	exit(status);
}

int	execute_builtin_command(t_command *cmd, t_bool is_direct,
		t_shell_env *shell_env)
{
	const char		*command = cmd->command->words->word->word;
	t_builtin_func	*f;
	int				status;
	int				fd_arr[3];

	if (is_direct && cmd->command->redirects)
	{
		if (!save_stdfd(fd_arr))
			return (EXECUTION_FAILURE);
		if (do_redirections(cmd->command->redirects, shell_env))
			return (close_stdfd(fd_arr), EXECUTION_FAILURE);
	}
	f = get_builtin_func(command);
	if (!f)
		return (internal_error(BUILTIN_ERR_STR, command), EXECUTION_FAILURE);
	status = (*f)(cmd->command->words->next, shell_env);
	if ((*f) == builtin_exit)
		return (handle_exit_command(cmd, shell_env, status));
	if (is_direct && cmd->command->redirects)
	{
		if (!reset_stdfd(fd_arr))
			return (close_stdfd(fd_arr), EXECUTION_FAILURE);
		close_stdfd(fd_arr);
	}
	return (status);
}
