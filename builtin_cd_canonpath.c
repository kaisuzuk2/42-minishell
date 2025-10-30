/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_canonpath.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:15:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/30 10:09:15 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// 絶対パスの移動 ../ ./ / .. .
// ../dir

static void skip_slashes(char **p)
{
	while (**p == '/')
		(*p)++;
}

t_bool	is_pathsep(char c)
{
	return (c == '/' || c == 0);
}

static void remove_parent(char **q, char *base)
{
	if (*q > base)
	{
		(*q)--;
		while (*(q) > base && *(*q - 1) != '/')
			(*q)--;
	}
}

static t_bool is_abst_path(char **p, char **q, char *base)
{
	if ((*p)[0] == '.' && (*p)[1] == '/' && (*p)[2] == '\0')
		return ((*p)++, TRUE);
	if ((*p)[0] == '.' && (*p)[1] == '.' && is_pathsep((*p)[2]))
		return ((*p) += 2, remove_parent(q, base), TRUE);
	return (FALSE);
}

char *sh_canonpath(char *tmp_path)
{
	char *base;
	char *p;
	char *q;

	base = savestring(tmp_path);
	if (!base)
		return (NULL);
	p = base;
	q = base;
	while (*p)
	{
		if (*p == '/')
		{
			*q++ = *p++;
			skip_slashes(&p);
		}
		if (!is_abst_path(&p, &q, base) && *p)
			*q++ = *p++;
	}
	*q = '\0';
	return (base);
}

// static char	*sh_canonpath(char *tmp_path)
// {
// 	char	*t;
// 	char	*p;
// 	char	*q;
// 	char	*base;

// 	t = savestring(tmp_path);
// 	if (!t)
// 		return (NULL); // ### TODO: エラー処理
// 	p = t;
// 	q = t;
// 	p++;
// 	q++;
// 	base = p;
// 	while (*p)
// 	{
// 		if (*p == '/')
// 		{
// 			*q = *p;
// 			q++;
// 			p++;
// 		}
// 		while (*p && *p == '/')
// 			p++;
// 		if (p[0] == '.' && (p[1] == '/' || p[1] == '\0'))
// 			p += 1;
// 		else if (p[0] == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0'))
// 		{
// 			p += 2;
// 			q--;
// 			if (q > base)
// 				while (--q > base && !(*q == '/'))
// 					;
// 		}
// 		else
// 		{
// 			*q = *p;
// 			p++;
// 			q++;
// 		}
// 	}
// 	*q = '\0';
// 	return (t);
// }