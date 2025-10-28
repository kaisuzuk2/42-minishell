/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:03:44 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 13:49:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_variable
{
	char *name; // key
	char *value;
	char *exportstr; // FOO=var
	int attributes; // exxport flg
} t_shell_var;

typedef struct s_vlist
{
	struct s_vlist *next;
	t_shell_var *var;
} t_varlist;

typedef struct s_shell_env
{
	t_varlist *env;
	char *tcwd;
} t_shell_env;

#endif