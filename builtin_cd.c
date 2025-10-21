/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:03:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/21 10:52:49 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 引数なし = home error = HOME not set
// 引数多すぎ = 移動なし error = too many arguments
// -だけ = oldpwdに移動 error = OLDPWD not set

// lcd_printpath = $CDPATHのパスに移動したとき・-で移動したとき
// $CDPATHとは

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


static int	change_to_directory(char *new_path)
{
	return (chdir(new_path));
}

int	builtin_cd(t_word_list *list, t_varlist *env)
{
	char *dirname;
	char *current_path;
	char *new_path;
	
	if (list->next)
	{
		printf("too many arguments\n");
		return (99); // ### TODO: エラー処理
	}
	dirname = list->word->word;
	current_path = NULL;
	current_path = list_getenv(env, "PWD");
	new_path = sh_makepath(current_path, dirname);
	printf("### %s\n", new_path);
	return (change_to_directory(new_path));
}