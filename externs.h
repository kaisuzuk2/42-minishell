/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/27 09:34:22 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNS_H
# define EXTERNS_H

# include "command.h"
# include "variables.h"

// tokenize.c
t_token_list	*tokenize(char *line);

// parser.c
t_command		*parser(t_token_list *token);

// expand.c
t_bool			expand(t_varlist *env, t_command *command);

// subst.c
char			*expand_string_to_string(t_varlist *env, char *document);

// list.c
size_t			list_length(t_generic_list *list);

// execute_pipeline.c
int				execute_cmd(t_command *cmd, t_varlist *env);

// findcmd.c
char			*search_for_command(char *cmd, t_varlist *env);
char			*savestring(char *str);

// strvec.c
char			**strvec_from_word_list(t_word_list *list);

// ft_mkstmp
int				ft_mkstemp(char **template);

// redir.c
int				do_redirections(t_redirect *redirect, t_varlist *env);

// make_cmd.c
char			*make_here_document(char *here_doc_eof);

// builtin.c
int				execute_builtin_command(t_command *cmd,
					const t_builtin *builtin_table, const size_t table_size,  t_varlist *env);
t_bool			is_builtin(char *command, const t_builtin *builtin_table, const size_t table_size);

// builtin_echo.c
int				builtin_echo(t_word_list *list, t_varlist *env);

// builtin_env.c
int				builtin_env(t_word_list *list, t_varlist *env);

// builtin_export.c
int				builtin_export(t_word_list *list, t_varlist *env);

// builtin_export.c
int				builtin_export(t_word_list *list, t_varlist *env);

// builtin_unset.c
int				builtin_unset(t_word_list *list, t_varlist *env);

// builtin_pwd.c
int				builtin_pwd(t_word_list *list, t_varlist *env);

// builtin_cd.c
int				builtin_cd(t_word_list *list, t_varlist *env);

// variables.c
t_varlist		*initialize_shell_variables(char **envp);
char			*list_getenv(t_varlist *env, char *key);
char			**get_env_arr(t_varlist *env);
t_shell_var		*create_shell_var(void);
t_varlist		*create_varlist(void);
t_bool			set_variable_name(t_shell_var *map, char *env);
t_bool			set_variable_value(t_shell_var *map, char *env);
t_bool			set_variable_exportstr(t_shell_var *map, char *env);
void			set_variable_attributes(t_shell_var *map);
t_bool			bind_variable(t_varlist *env, char *key, char *value);
t_shell_var		*list_getshell_var(t_varlist *env, char *key);
t_bool			add_variable_item(t_varlist *env, char *exportstr);

#endif