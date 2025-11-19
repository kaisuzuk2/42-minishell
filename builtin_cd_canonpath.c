/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_canonpath.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:15:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 11:52:49 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin_cd_utils.c
t_bool			is_pathsep(char c);

static void	skip_slashes(char **p)
{
	while (**p == '/')
		(*p)++;
}

static void	remove_parent(char **q, char *base)
{
	if (*q > (base + 1))
	{
		(*q)--;
		while ((*q) > (base + 1) && *(*q - 1) != '/')
			(*q)--;
		while ((*q) > (base + 1) && *(*q - 1) == '/')
			(*q)--;
	}
}

static t_bool	is_abst_path(char **p, char **q, char *base)
{
	if (*q > base && *(*q - 1) != '/')
		return (FALSE);
	if ((*p)[0] == '.' && is_pathsep((*p)[1]))
	{
		(*p)++;
		if ((**p) && is_pathsep(**p))
			(*p)++;
		return (TRUE);
	}
	if ((*p)[0] == '.' && (*p)[1] == '.' && is_pathsep((*p)[2]))
		return ((*p) += 2, remove_parent(q, base), TRUE);
	return (FALSE);
}

static void	trim_last_slash(char **q, char *base)
{
	if (ft_strlen(base) <= 1)
		return ;
	while ((*q) > (base + 1) && *(*q - 1) == '/')
		(*q)--;
}

char	*sh_canonpath(char *tmp_path)
{
	char	*base;
	char	*p;
	char	*q;

	base = savestring(tmp_path);
	if (!base)
		return (fatal_error("malloc", MALLOC_ERR_STR), NULL);
	p = base;
	q = base;
	while (*p)
	{
		if (*p == '/')
		{
			*q++ = *p++;
			skip_slashes(&p);
		}
		if (*p && !is_abst_path(&p, &q, base))
			*q++ = *p++;
	}
	trim_last_slash(&q, base);
	*q = '\0';
	return (base);
}
