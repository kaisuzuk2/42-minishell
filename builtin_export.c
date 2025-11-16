/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:37:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 16:51:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO: sort

static void map_swap(t_shell_var_map *m1, t_shell_var_map *m2)
{
	t_shell_var_map tmp;

	tmp = *m1;
	*m1 = *m2;
	*m2 = tmp;
}

static void sort_var_arr(t_shell_var_map *env, size_t size)
{
	int i;
	int j;

	i = 0;
	if (size <= 0)
		return ;
	while (i < size)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(env[j].name, env[j + 1].name) > 0)
				map_swap(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

// static int	show_var_attributes(t_varlist *env)
// {
// 	char	**envstr;
// 	int		i;

// 	i = 0;
// 	while (env)
// 	{
// 		if (!is_exported(env->var))
// 		{
// 			env = env->next;
// 			continue ;
// 		}
// 		ft_dprintf(STDOUT_FILENO, "declare -x %s", env->var->name);
// 		if (env->var->value)
// 			ft_dprintf(STDOUT_FILENO, "=\"%s\"", env->var->value);
// 		ft_dprintf(STDOUT_FILENO, "\n");
// 		i++;
// 		env = env->next;
// 	}
// 	return (EXECUTION_SUCCESS);
// }

static void print_var_map(t_shell_var_map *env, size_t size)
{
	int i;

	i = 0;
	if (size <= 0)
		return ;
	while (i < size)
	{
		ft_dprintf(STDOUT_FILENO, "declare -x %s", env[i].name);
		if (env[i].value)
			ft_dprintf(STDOUT_FILENO, "=\"%s\"", env[i].value);
		ft_dprintf(STDOUT_FILENO, "\n");
		i++;
	}
}

static int show_var_attributes(t_varlist *env)
{
	size_t size = list_length((t_generic_list *)env);
	t_shell_var_map *var_arr;
	int	i;

	var_arr = (t_shell_var_map *)xcalloc(size + 1, sizeof(t_shell_var_map));
	if (!var_arr)
		return (EXECUTION_MEMERR);
	i = 0;
	while (env)
	{
		if (!is_exported(env->var))
		{
			env = env->next;
			continue ;
		}
		var_arr[i].name = savestring(env->var->name);
		if (!env->var->value)
			var_arr[i].value = NULL;
		else
			var_arr[i].value = savestring(env->var->value);
		env = env->next;
		i++;
	}
	sort_var_arr(var_arr, --i);
	print_var_map(var_arr, i);
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
	char		*new_exportstr;
	char		*value;
	t_bool		res;

	key = get_env_key(exportstr);
	if (!key)
		return (FALSE);
	key_env = list_getshell_var(env, key);
	free(key);
	if (!ft_strchr(exportstr, '='))
	{
		if (!key_env)
			return (update_variable_item(env, exportstr, 1));
		return (set_variable_attributes(key_env, 1), TRUE);
	}
	if (!ft_strchr(exportstr, '+'))
		return (update_variable_item(env, exportstr, 1));
	return (add_export(env, key_env, exportstr));
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
