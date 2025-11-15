/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:17:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 11:53:02 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "command.h"
#include "variables.h"

typedef int t_builtin_func (t_word_list *list, t_shell_env *env);

typedef struct s_builtin
{
	char *name;
	t_builtin_func *f;
} t_builtin;

typedef struct s_builtin_table
{
	const t_builtin *table;
	size_t size;
} t_builtin_table;

# define EX_CONNECT 0
# define EX_SIMPLE 1

#endif