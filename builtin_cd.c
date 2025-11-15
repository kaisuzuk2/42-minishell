/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:03:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 15:01:41 by kaisuzuk         ###   ########.fr       */
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


char	*get_interpret_cd(t_word_list *list, t_varlist *env);


int	update_pwd(char *tdir, t_shell_env *shell_env);

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
		return (-1);
	tdir = sh_canonpath(t);
	free(t);
	if (!chdir(tdir))
		return (update_pwd(tdir, shell_env));
	sys_error("cd");
	free(tdir);
	return (EXECUTION_FAILURE);
}

static int	try_cdpath(char *dirname, t_shell_env *shell_env)
{
	int		i;
	char	**cdpath;
	char	*newpath;

	i = 0;
	cdpath = ft_split(list_getenv(shell_env->env, "CDPATH"), ':');
	if (!cdpath)
		return (-1);
	while (cdpath[i])
	{
		newpath = sh_makepath(cdpath[i], dirname);
		if (!newpath)
			return (dispose_char_arr(cdpath), -1);
		if (!change_to_directory(newpath, shell_env))
			return (free(newpath), dispose_char_arr(cdpath), EXECUTION_SUCCESS);
		free(newpath);
		i++;
	}
	dispose_char_arr(cdpath);
	return (EXECUTION_FAILURE);
}

int	builtin_cd(t_word_list *list, t_shell_env *shell_env)
{
	char	*dirname;
	char	*t;
	int		status;

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
		status = try_cdpath(dirname, shell_env);
		if (status < 0)
			return (-1);
		else if (!status)
			return (EXECUTION_SUCCESS);
	}
	return (change_to_directory(dirname, shell_env));
}
