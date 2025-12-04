/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:03:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/12/05 02:21:11 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin_cd_utils.c
t_bool		valid_cd_path(t_word_list *list);
t_bool		is_absolute_pathname(const char *string);
t_bool		is_same_file(const char *path1, const char *path2,
				struct stat *stp1, struct stat *stp2);

// builtin_cd_interpret.c
char		*get_interpret_cd(t_word_list *list, t_varlist *env);
t_bool		is_interpret_cd(t_word_list *list);
t_bool		is_interpret_home(t_word_list *list);
t_bool		is_interpret_oldpwd(t_word_list *list);

// builtin_cd_env.c
int			update_pwd(char *tdir, t_shell_env *shell_env);

// builtin_cd_canonpath.c
char		*sh_canonpath(char *tmp_path);

static int	sh_makepath(char *path, char *dir, char **res)
{
	char	*tmp;

	if (!path || *path == 0)
	{
		*res = getcwd(NULL, 0);
		if (!res)
		{
			sys_error("getcwd failed");
			return (EXECUTION_ERR);
		}
	}
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (EXECUTION_MEMERR);
	*res = ft_strjoin(tmp, dir);
	if (!*res)
		return (free(tmp), EXECUTION_MEMERR);
	free(tmp);
	return (EXECUTION_SUCCESS);
}

static int	make_absolute(char *dirname, char *cwd, char **t)
{
	if (cwd == 0 || dirname[0] == '/')
	{
		*t = savestring(dirname);
		if (!t)
			return (fatal_error("malloc", MALLOC_ERR_STR), EXECUTION_MEMERR);
		return (EXECUTION_SUCCESS);
	}
	return (sh_makepath(cwd, dirname, t));
}

static int	change_to_directory(char *newdir, t_shell_env *shell_env)
{
	char	*tcwd;
	char	*tdir;
	char	*t;
	int		status;

	tcwd = NULL;
	tcwd = get_current_working_directory(shell_env);
	if (!tcwd || !is_same_file(tcwd, ".", (struct stat *)0, (struct stat *)0))
		tcwd = getcwd(NULL, 0);
	if (!tcwd)
		return (sys_error("getcwd failed"), EXECUTION_ERR);
	status = make_absolute(newdir, tcwd, &t);
	if (status < 0)
		return (status);
	tdir = sh_canonpath(t);
	if (!tdir)
		return (EXECUTION_MEMERR);
	if (!chdir(tdir))
	{
		free(t);
		return (update_pwd(tdir, shell_env));
	}
	return (free(t), free(tdir), builtin_error("cd", newdir, strerror(errno)), EXECUTION_FAILURE);
}

static int	try_cdpath(char *dirname, t_shell_env *shell_env)
{
	int		i;
	char	**cdpath;
	char	*newpath;
	int		status;

	i = 0;
	cdpath = ft_split(get_listenv(shell_env->env, CDPATH), ':');
	if (!cdpath)
		return (EXECUTION_MEMERR);
	while (cdpath[i])
	{
		status = sh_makepath(cdpath[i], dirname, &newpath);
		if (status < 0)
			return (status);
		status = change_to_directory(newpath, shell_env);
		if (status < 0)
			return (status);
		if (!status)
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
	if (!is_absolute_pathname(dirname) && get_listenv(shell_env->env, CDPATH))
	{
		status = try_cdpath(dirname, shell_env);
		if (!status)
			return (status);
		if (status < 0)
			return (status);
	}
	status = change_to_directory(dirname, shell_env);
	if (status == EXECUTION_ERR)
		return (EXECUTION_FAILURE);
	return (status);
}
