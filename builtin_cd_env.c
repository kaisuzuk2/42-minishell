/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:59:01 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 15:17:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	bindpwd(t_varlist *env, char *key, char *value)
{
	char		*exportstr;
	int			flag;
	t_shell_var	*env_var;

	exportstr = create_exportstr(key, value);
	if (!exportstr)
		return (FALSE);
	env_var = list_getshell_var(env, key);
	if (!env_var || !env_var->attributes)
		flag = 0;
	else
		flag = 1;
	if (!update_variable_item(env, exportstr, flag))
		return (free(exportstr), FALSE);
	free(exportstr);
	return (TRUE);
}

int	update_pwd(char *tdir, t_shell_env *shell_env)
{
	if (!set_current_working_directory(shell_env, tdir))
		return (free(tdir), EX_FATAL_ERROR);
	if (!bindpwd(shell_env->env, "OLDPWD", list_getenv(shell_env->env, "PWD")))
		return (free(tdir), EX_FATAL_ERROR);
	if (!bindpwd(shell_env->env, "PWD", tdir))
		return (free(tdir), EX_FATAL_ERROR);
	free(tdir);
	return (EXECUTION_SUCCESS);
}
