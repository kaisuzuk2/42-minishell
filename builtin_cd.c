/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:03:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/30 16:06:12 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 引数なし = home error = HOME not set
// 引数多すぎ = 移動なし error = too many arguments
// -だけ = oldpwdに移動 error = OLDPWD not set

// lcd_printpath = $CDPATHのパスに移動したとき・-で移動したとき
// $CDPATHとは

// OLDPWDはexportされていない
// oldpwd削除しても再度変数が作成されて値が設定される

// /foo/var && ../ && ./ && .

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

// ###TODO: チルダ展開する
// シンボリックリンクを解決しないからgetcwd使うとおかしくなる
static char	*sh_makepath(char *path, char *dir)
{
	char	*tmp;
	char	*res;

	if (!path || *path == 0)
		return (getcwd(NULL, 0));
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL); // ### TODO: エラー処理
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

	exportstr = create_exportstr(key, value);
	if (!exportstr)
		return (FALSE);
	if (!update_variable_item(env, exportstr))
		return (free(exportstr), FALSE);
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
	tdir = sh_canonpath(t);
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

// int builtin_cd(t_word_list *list, t_shell_env *shell_env)
// {
// 	char *dirname;
// 	int lcd_printpath;
// 	char *t;
// 	char *new_path;
// 	int e;
// 	t_varlist *env;

// 	env = shell_env->env;
// 	lcd_printpath = 0;
// 	if (!list || !list->word->word[0])
// 	{
// 		dirname = list_getenv(env, "HOME");
// 		if (!dirname)
// 		{
// 			printf("HOME not set\n"); // ### TODO: エラー処理
// 			return (99);
// 		}
// 	}
// 	else if (list->word->word[0] == '-' && list->word->word[1] == '\0')
// 	{
// 		dirname = list_getenv(env, "OLDPWD");
// 		if (!dirname)
// 		{
// 			printf("OLDPWD not set\n"); // ### TODO: エラー処理
// 			return (99);
// 		}
// 		lcd_printpath = 1;
// 	}
// 	else
// 		dirname = list->word->word;

// 	t = make_absolute(dirname, list_getenv(env, "PWD"));
// 	if (!t)
// 		return (99); // ### TODO: エラー処理
// 	new_path = sh_canonpath(t);
// 	free(t);
// 	if (!new_path)
// 		return (99); // ### TODO: エラー処理
// 	if (!change_to_directory(new_path))
// 	{
// 		bindpwd(env, list_getenv(env, "PWD"), new_path);
// 		return (0);
// 	}
// 	// e = errno;
// 	return (99); // ### TODO: エラー処理
// }

// int	builtin_cd(t_word_list *list, t_varlist *env)
// {
// 	char *dirname;
// 	char *current_path;
// 	char *new_path;

// 	if (list->next)
// 	{
// 		printf("too many arguments\n");
// 		return (99); // ### TODO: エラー処理
// 	}
// 	dirname = list->word->word;
// 	current_path = NULL;
// 	current_path = list_getenv(env, "PWD");
// 	new_path = sh_makepath(current_path, dirname);
// 	printf("### %s\n", new_path);
// 	if (!chdir(new_path))
// 		bindpwd(env, current_path, new_path);
// }