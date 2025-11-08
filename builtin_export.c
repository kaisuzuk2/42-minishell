/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:37:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/08 09:17:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO: 設定がすでにされている場合のケース
// +=のケース

// ### TODO: クォートは除去してから入れる

static int show_var_attributes(t_varlist *env)
{
	char **envstr;
	int i;

	envstr = get_env_arr(env);  // varlistのexportstr出力したらええのでは
	if (!envstr)
		return (EX_FATAL_ERROR);
	i = 0;
	while (envstr[i])
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s\n", envstr[i]);
		free(envstr[i]);
		i++;
	}
	return (EXECUTION_SUCCESS);
}

static t_bool is_valid_env_name(char *exportstr)
{
	if (ft_isdigit(*exportstr) || (!ft_isalnum(*exportstr) && !(*exportstr == '_')))
		return (FALSE);
	while (*exportstr)
	{
		if (*exportstr == '=' || (*exportstr == '+' && exportstr[1] == '=') )
			return (TRUE);
		if (!ft_isalnum(*exportstr) && !(*exportstr == '_'))
			return (FALSE);
		exportstr++;
	}
	return (TRUE);
}

static t_bool update_export(t_shell_env *shell_env, char *exportstr)
{
	char *key;
	t_shell_var *key_env;
	char *new_exportstr;
	char *value;
	t_bool res;
	
	if (!ft_strchr(exportstr, '+'))
		return (update_variable_item(shell_env, exportstr));
	key = get_env_key(exportstr);
	if (!key)
		return (FALSE);
	value = get_env_value(exportstr);
	if (!value)
		return (free(key), FALSE);
	printf("### %s, %s\n", key, value);
	key_env = list_getshell_var(shell_env->env, key);
	if (!key_env)
		return (free(key), free(value), FALSE);
	new_exportstr = ft_strjoin(key_env->exportstr, value);
	if (!new_exportstr)
		return (free(key), free(value), FALSE);
	res = update_variable_item(shell_env->env, new_exportstr);
	return (free(key), free(value), free(new_exportstr), res);
}

int builtin_export(t_word_list *list, t_shell_env *shell_env)
{
	t_bool flg;

	if (!list)
		return (show_var_attributes(shell_env->env));
	flg = TRUE;
	while (list)
	{
		if (!is_valid_env_name(list->word->word))
		{
			flg = FALSE;
			builtin_error("export", list->word->word, EXPORT_ERR);
			list = list->next;
			continue ;
		}
		if (!update_export(shell_env->env, list->word->word))
			return (EX_FATAL_ERROR);
		list = list->next;
	}
	if (!flg)
		return (EXECUTION_FAILURE);
	return (EXECUTION_SUCCESS);
}