/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:44:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 11:48:50 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_status(int s, t_shell_env *env)
{
	env->last_status = s;
}

t_bool	set_current_working_directory(t_shell_env *shell_env, char *value)
{
	if (shell_env->tcwd)
		free(shell_env->tcwd);
	shell_env->tcwd = savestring(value);
	if (!shell_env->tcwd)
		return (FALSE);
	return (TRUE);
}
