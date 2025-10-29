/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:03:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/29 12:15:33 by kaisuzuk         ###   ########.fr       */
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
static t_bool	is_pathsep(char c)
{
	return (c == '/' || c == 0);
}

static t_bool	is_absolute_pathname(const char *string)
{
	if (string == 0 || *string == '\0')
		return (FALSE);
	if (*string == '/')
		return (TRUE);
	if (string[0] == '.' && is_pathsep(string[1]))
		return (TRUE);
	if (string[0] == '.' && string[1] == '.' && is_pathsep(string[2]))
		return (TRUE);
	return (FALSE);
}

// ###TODO: チルダ展開する
// シンボリックリンクを解決しないからgetcwd使うとおかしくなる
static char	*sh_makepath(char *path, char *dir)
{
	char		*tmp;
	char *res;

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

// 絶対パスの移動 ../ ./ / .. .
// ../dir
static char *sh_canonpath(char *tmp_path)
{
	char *t;
	char *p;
	char *q;
	char *base;

	t = savestring(tmp_path);
	if (!t)
		return (NULL); // ### TODO: エラー処理
	
	p = t;
	q = t;
	p++;
	q++;
	base = p;

	while (*p)
	{
		if (*p == '/')
		{
			*q = *p;
			q++;
			p++;
		}
		while (*p && *p == '/')
			p++;
		if (p[0] == '.' && (p[1] == '/' || p[1] == '\0'))
			p += 1;
		else if (p[0] == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0'))
		{
			p += 2;
			q--;
			if (q > base)
				while (--q > base && !(*q == '/'));
		}
		else
		{
			*q = *p;
			p++;
			q++;
		}
	}
	*q = '\0';
	return (t);
}

static char *make_absolute(char *dirname, char *cwd)
{
	if (cwd == 0 || dirname[0] == '/')
		return (savestring(dirname));
	return (sh_makepath(cwd, dirname));	
}

static t_bool bindpwd(t_varlist *env, char *old_pwd, char *new_path)
{
	char *tmp;
	char *old_exportstr;
	char *new_exportstr;
	t_shell_var *shell_var;

	tmp = ft_strjoin("OLDPWD", "=");
	if (!tmp)
		return (99); // ### TODO: エラー処理
	old_exportstr = ft_strjoin(tmp, old_pwd);
	if (!old_exportstr)
		return (free(tmp), 99); // ### TODO: エラー処理
	
	tmp = ft_strjoin("PWD", "=");
	if (!tmp)
		return (99); // ### TODO: エラー処理
	new_exportstr = ft_strjoin(tmp, new_path);
	if (!new_exportstr)
		return (99); // ### TODO: エラー処理
	
	
	
	if (!list_getshell_var(env, "OLDPWD"))
	{
		update_variable_item(env, old_exportstr);	// ### TODO: エラー処理
	}
	else
	{
		shell_var = list_getshell_var(env, "OLDPWD");
		free(shell_var->value);
		free(shell_var->exportstr);
		shell_var->value = savestring(old_pwd); // ### TODO: エラー処理
		shell_var->exportstr = savestring(old_exportstr);
	}

	
	if (!list_getshell_var(env, "PWD"))
	{
		update_variable_item(env, new_exportstr);	// ### TODO: エラー処理
	}
	else
	{
		shell_var = list_getshell_var(env, "PWD");
		free(shell_var->value);
		free(shell_var->exportstr);
		shell_var->value = savestring(new_path); // ### TODO: エラー処理
		shell_var->exportstr = savestring(new_exportstr);
	}

	return (TRUE);
}


static int	change_to_directory(char *path)
{
	return (chdir(path));
}

int builtin_cd(t_word_list *list, t_shell_env *shell_env)
{
	char *dirname;
	int lcd_printpath;
	char *t;
	char *new_path;
	int e;
	t_varlist *env;

	env = shell_env->env;
	lcd_printpath = 0;
	if (!list || !list->word->word[0])
	{
		dirname = list_getenv(env, "HOME");
		if (!dirname)
		{
			printf("HOME not set\n"); // ### TODO: エラー処理
			return (99);
		}
	}
	else if (list->word->word[0] == '-' && list->word->word[1] == '\0')
	{
		dirname = list_getenv(env, "OLDPWD");
		if (!dirname)
		{
			printf("OLDPWD not set\n"); // ### TODO: エラー処理
			return (99); 
		}
		lcd_printpath = 1;
	}
	else
		dirname = list->word->word;
	
	t = make_absolute(dirname, list_getenv(env, "PWD"));
	if (!t)
		return (99); // ### TODO: エラー処理
	new_path = sh_canonpath(t);
	free(t);
	if (!new_path)
		return (99); // ### TODO: エラー処理
	if (!change_to_directory(new_path))
	{
		bindpwd(env, list_getenv(env, "PWD"), new_path);
		return (0);
	}
	// e = errno;
	return (99); // ### TODO: エラー処理
}

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