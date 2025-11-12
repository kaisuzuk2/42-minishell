/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:03:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/12 10:06:30 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin_cd_utils.c
t_bool			is_interpret_home(t_word_list *list);
t_bool			is_interpret_oldpwd(t_word_list *list);
t_bool			is_interpret_cd(t_word_list *list);
t_bool			valid_cd_path(t_word_list *list);
t_bool			is_same_file(const char *path1, const char *path2,
					struct stat *stp1, struct stat *stp2);
t_bool			is_absolute_pathname(const char *string);

// buintin_cd_canonpath.c
char			*sh_canonpath(char *tmp_path);
t_bool			is_pathsep(char c);

static char	*sh_makepath(char *path, char *dir)
{
	char	*tmp;
	char	*res;

	if (!path || *path == 0)
		return (getcwd(NULL, 0));
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL); 
	res = ft_strjoin(tmp, dir);
	if (!res)
		return (free(tmp), NULL);
	free(tmp);
	return (res);
}

static char	*make_absolute(char *dirname, char *cwd)
{
	if (cwd == 0 || dirname[0] == '/')
		return (savestring(dirname));
	return (sh_makepath(cwd, dirname));
}

static t_bool	bindpwd(t_varlist *env, char *key, char *value)
{
	char	*exportstr;
	int flag;
	t_shell_var *env_var;
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

static int	change_to_directory(char *newdir, t_shell_env *shell_env)
{
	char	*tcwd;
	char	*tdir;
	char	*t;

	tcwd = NULL;
	tcwd = get_current_working_directory(shell_env);
	if (!tcwd || !is_same_file(tcwd, ".", (struct stat *)0, (struct stat *)0))
		tcwd = getcwd(NULL, 0);
	if (!tcwd)
		return (sys_error("getcwd failed"), 0);
	t = make_absolute(newdir, tcwd);
	if (!t)
		return (0);
	tdir = sh_canonpath(t);
	free(t);
	if (!chdir(tdir))
	{
		if (!set_current_working_directory(shell_env, tdir))
			return (EX_FATAL_ERROR);
		if (!bindpwd(shell_env->env, "OLDPWD", list_getenv(shell_env->env,
					"PWD")))
			return (EX_FATAL_ERROR);
		if (!bindpwd(shell_env->env, "PWD", tdir))
			return (EX_FATAL_ERROR);
		free(tdir);
		return (0);
	}
	sys_error("cd");
	return (1);
}

char	*get_interpret_cd(t_word_list *list, t_varlist *env)
{
	char	*dirname;

	if (is_interpret_home(list))
	{
		dirname = list_getenv(env, "HOME");
		if (!dirname)
		{
			builtin_error("cd", NULL, "HOME not set");
			return (NULL);
		}
	}
	else
	{
		dirname = list_getenv(env, "OLDPWD");
		if (!dirname)
		{
			builtin_error("cd", NULL, "OLDPWD not set");
			return (NULL);
		}
	}
	return (dirname);
}

/*

PWD OLDPWDが消えている場合環境変数としては再設定しない
しかしシェル変数としては再設定する

*/

int	builtin_cd(t_word_list *list, t_shell_env *shell_env)
{
	char	*dirname;
	char	*t;
	char	**cdpath;
	int i;
	char *newpath;

	if (!valid_cd_path(list))
		return (EXIT_FAILURE);
	if (is_interpret_cd(list))
	{
		dirname = get_interpret_cd(list, shell_env->env);
		if (!dirname)
			return (EXIT_FAILURE);
	}
	else
		dirname = list->word->word;
	if (!is_absolute_pathname(dirname) && list_getenv(shell_env->env, "CDPATH"))
	{
		i = 0;
		cdpath = ft_split(list_getenv(shell_env->env, "CDPATH"), ':');
		if (!cdpath)
			return (EX_FATAL_ERROR);
		while (cdpath[i])
		{
			newpath = sh_makepath(cdpath[i], dirname);
			if (!newpath)
				return (EX_FATAL_ERROR);
			if (!change_to_directory(newpath, shell_env))
				return (0);
			i++;
		}
	}
	change_to_directory(dirname, shell_env);
	return (0);
}
