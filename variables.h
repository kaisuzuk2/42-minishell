/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:03:44 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 18:34:15 by kaisuzuk         ###   ########.fr       */
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

// variables.c
t_shell_env		*initialize_shell_variables(char **envp);;


// variables_alloc.c ### TODO: newにしたほうがよくね？
t_shell_var	*create_shell_var(void);
t_varlist	*create_varlist(void);

//variables_set.c
t_bool	set_variable_name(t_shell_var *map, char *env);
t_bool	set_variable_value(t_shell_var *map, char *env);
t_bool	set_variable_exportstr(t_shell_var *map, char *env);
void set_variable_attributes(t_shell_var *map);

#endif