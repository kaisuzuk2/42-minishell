/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:37:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 14:06:20 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_var_map	*make_shell_env_map(t_shell_var_map *var_arr, t_varlist *env);
void			sort_var_arr(t_shell_var_map *env, size_t size);
void			free_env_map(t_shell_var_map *env);
void			print_var_map(t_shell_var_map *env);

static int	show_var_attributes(t_varlist *env)
{
	t_shell_var_map	*var_arr;
	size_t			size;

	var_arr = (t_shell_var_map *)xcalloc(list_length((t_generic_list *)env) + 1,
			sizeof(t_shell_var_map));
	if (!var_arr)
		return (EXECUTION_MEMERR);
	if (!make_shell_env_map(var_arr, env))
		return (EXECUTION_MEMERR);
	size = 0;
	while (var_arr[size].name)
		size++;
	sort_var_arr(var_arr, size);
	print_var_map(var_arr);
	free_env_map(var_arr);
	return (EXECUTION_SUCCESS);
}

static t_bool	is_valid_env_name(char *exportstr)
{
	if (ft_isdigit(*exportstr) || (!ft_isalnum(*exportstr)
			&& !(*exportstr == '_')))
		return (FALSE);
	while (*exportstr)
	{
		if (*exportstr == '=' || (*exportstr == '+' && exportstr[1] == '='))
			return (TRUE);
		if (!ft_isalnum(*exportstr) && !(*exportstr == '_'))
			return (FALSE);
		exportstr++;
	}
	return (TRUE);
}

static t_bool	add_export(t_varlist *env, t_shell_var *key_env,
		char *exportstr)
{
	char	*value;
	char	*new_exportstr;
	t_bool	res;

	value = get_env_value(exportstr);
	if (!value)
		return (FALSE);
	new_exportstr = ft_strjoin(key_env->exportstr, value);
	free(value);
	if (!new_exportstr)
		return (FALSE);
	res = update_variable_item(env, new_exportstr, 1);
	return (free(new_exportstr), res);
}

static t_bool	update_export(t_varlist *env, char *exportstr)
{
	char		*key;
	t_shell_var	*key_env;
	char		*key_p;

	key = get_env_key(exportstr);
	if (!key)
		return (FALSE);
	key_env = get_shell_var(env, key);
	free(key);
	if (!ft_strchr(exportstr, '='))
	{
		if (!key_env)
			return (update_variable_item(env, exportstr, 1));
		return (set_variable_attributes(key_env, 1), TRUE);
	}
	key_p = ft_strchr(exportstr, '+');
	if ((key_p && key_p[1] == '=') && key_env)
		return (add_export(env, key_env, exportstr));
	return (update_variable_item(env, exportstr, 1));
}

int	builtin_export(t_word_list *list, t_shell_env *shell_env)
{
	t_bool	flg;

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
			return (EXECUTION_MEMERR);
		list = list->next;
	}
	if (!flg)
		return (EXECUTION_FAILURE);
	return (EXECUTION_SUCCESS);
}
