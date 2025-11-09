/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:13:08 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/09 12:49:05 by kaisuzuk         ###   ########.fr       */
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

t_bool	is_builtin(char *command, const t_builtin *builtin_table,
		const size_t table_size)
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

t_builtin_table	get_builtin_table(void)
{
	t_builtin_table	info;

	static const t_builtin builtin_table[] = {
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

static int	handle_exit_command(t_command *cmd, t_shell_env *shell_env,
		int status)
{
	if (status > 255)
		return (EXIT_FAILURE);
	dispose_command(cmd->head);
	dispose_env(shell_env);
	exit(status);
}

t_bool  save_stdfd(int *fd_arr)
{
	int i;

	fd_arr[STDIN_FILENO] = dup(STDIN_FILENO);
	fd_arr[STDOUT_FILENO] = dup(STDOUT_FILENO);
	fd_arr[STDERR_FILENO] = dup(STDERR_FILENO);
	i = 0;
	while (i < STDFD_SIZE)
	{
		if (fd_arr[i] < 0)
			return (sys_error("dup2 failed"), FALSE);
		i++;
	}
	return (TRUE);
}

t_bool reset_stdfd(int *fd_arr)
{
	if (dup2(fd_arr[STDIN_FILENO], STDIN_FILENO) < 0)	
		return (sys_error("dup2 failed"), FALSE);
	if (dup2(fd_arr[STDOUT_FILENO], STDOUT_FILENO) < 0)
		return (sys_error("dup2 failed"), FALSE);
	if (dup2(fd_arr[STDERR_FILENO], STDERR_FILENO) < 0)
		return (sys_error("dup2 failed"), FALSE);
	return (TRUE);
}

void close_stdfd(int *fd_arr)
{
	int i;

	i = 0;
	while (i < STDFD_SIZE)
	{
		close(fd_arr[i]);
		i++;
	}
}

int	execute_builtin_command(t_command *cmd, t_pipefd pipefd,
		t_shell_env *shell_env)
{
	char *command;
	t_word_list *arg;
	t_builtin_func *f;
	int status;
	t_builtin_table builtin_info;
	int fd_arr[3];

	if (cmd->command->redirects)
	{
		if (!save_stdfd(fd_arr))
			return (EXECUTION_FAILURE);
		if (do_redirections(cmd->command->redirects, shell_env))
			return (close_stdfd(fd_arr), EXECUTION_FAILURE);
	}
	builtin_info = get_builtin_table();
	command = cmd->command->words->word->word;
	f = NULL;
	f = find_builtin_func(command, builtin_info.table, builtin_info.size);
	if (!f)
		return (internal_error(BUILTIN_ERR_STR, command), EXECUTION_FAILURE);
	arg = cmd->command->words->next;
	status = (*f)(arg, shell_env);
	if ((*f) == builtin_exit)
		return (handle_exit_command(cmd, shell_env, status));
	if (cmd->command->redirects)
		reset_stdfd(fd_arr);
	return (status);
}