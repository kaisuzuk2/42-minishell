/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:03:44 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 12:18:03 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_variable_map
{
	char			*name;
	char			*value;
}					t_shell_var_map;

typedef struct s_variable
{
	char			*name;
	char			*value;
	char			*exportstr;
	t_bool			attributes;
}					t_shell_var;

typedef struct s_vlist
{
	struct s_vlist	*next;
	t_shell_var		*var;
}					t_varlist;

typedef struct s_shell_env
{
	t_varlist		*env;
	char			*tcwd;
	int				last_status;
}					t_shell_env;

// variables.c
t_shell_env		*initialize_shell_variables(char **envp);

// variables_set.c
void			set_variable_attributes(t_shell_var *map, t_bool flag);
t_bool			set_variable_exportstr(t_shell_var *map, char *env);
t_bool			set_variable_value(t_shell_var *map, char *env);
t_bool			set_variable_name(t_shell_var *map, char *env);

// variables_get.c
char			*get_env_value(char *env);
char			*get_env_key(char *env);

// variables_alloc.c
char			*create_exportstr(char *key, char *value);
t_varlist		*create_varlist(void);
t_shell_var		*create_shell_var(void);

#endif