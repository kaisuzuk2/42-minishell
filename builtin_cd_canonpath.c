/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_canonpath.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:15:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/30 10:11:12 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
