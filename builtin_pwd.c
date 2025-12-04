/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:56:10 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/12/05 02:20:54 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1) stat tcwd
2) if correct print tcwd
   else getcwd
		if success print getcwd value
		else print $PWD or the_current_working_directory value 
		(Possibly deleted directory)
*/

int	builtin_pwd(t_word_list *list, t_shell_env *shell_env)
{
	char	*directory;

	(void)list;
	if (shell_env->tcwd)
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", shell_env->tcwd);
		return (EXECUTION_SUCCESS);
	}
	else
		directory = getcwd(NULL, 0);
	if (!directory)
		return (sys_error("getcwd failed"), EXECUTION_FAILURE);
	ft_dprintf(STDOUT_FILENO, "%s\n", directory);
	free(directory);
	return (EXECUTION_SUCCESS);
}
