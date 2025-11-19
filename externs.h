/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 10:38:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNS_H
# define EXTERNS_H

# include "command.h"
# include "variables.h"

/* **************************************************************** */
/*										*/
/*				env					*/
/*										*/
/* **************************************************************** */

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

// env.c
t_bool			update_variable_item(t_varlist *env, char *exportstr,
					t_bool flag);
t_bool			update_key_value(t_varlist *env, char *key, char *value,
					int flag);
t_bool			is_underbar(t_shell_var *env_var);
t_bool			is_exported(t_shell_var *env_var);

// env_set.c
t_bool			set_variable_items(t_shell_var *var, char *exportstr, int flg);
t_bool			set_current_working_directory(t_shell_env *shell_env,
					char *value);
void			set_last_status(int s, t_shell_env *env);

// env_get.c
t_shell_var		*get_shell_var(t_varlist *env, char *key);
char			*get_listenv(t_varlist *env, char *key);
char			**get_env_arr(t_varlist *env);
char			*get_current_working_directory(t_shell_env *shell_env);
int				get_last_status(t_shell_env *shell_env);

/* **************************************************************** */
/*										*/
/*				tokenize					*/
/*										*/
/* **************************************************************** */

// tokenize.c
t_token_list	*tokenize(char *line, t_shell_env *shell_env);

// tokenize_utils_tokenkinds.c
t_bool			is_shellblank(char c);
char			*is_metacharacter(char c);
t_bool			is_word(char *line);
t_bool			is_quote(char c);

/* **************************************************************** */
/*										*/
/*				parse					*/
/*										*/
/* **************************************************************** */

// parser.c
t_command		*parser(t_token_list *token, t_shell_env *shell_env);

// parser_utils.c
t_word_desc		*tokendup(t_word_desc *desc);

// parser_utils_tokenkinds.c
t_bool			is_redirect(t_token_kind kind);
t_bool			is_wordtoken(t_token_kind kind);
t_bool			is_eoftoken(t_token_kind kind);
t_bool			is_pipetoken(t_token_kind kind);

/* **************************************************************** */
/*										*/
/*				expand					*/
/*										*/
/* **************************************************************** */

// expand.c
t_bool			expand(t_command *command, t_shell_env *shell_env);

// expand_utils.c
char			*join_until(char *res, char **document, t_varlist *env);

// expand_ifs_split.c
char			**ifs_split(char const *s);

/* **************************************************************** */
/*										*/
/*				exec					*/
/*										*/
/* **************************************************************** */

// findcmd.c
t_bool			search_for_command(char *cmd, t_varlist *env, char **command);

// findcmd_utils.c
char			*savestring(char *str);

// redir.c
int				do_redirections(t_command *cmd, t_shell_env *shell_env);

// execute_pipeline.c
int				execute_pipeline(t_command *cmd, t_shell_env *shell_env);

// execute_pipeline_utils.c
int				file_isdir(char *command);

// execute_wait.c
pid_t			wait_for(pid_t lastpid);

// execute_builtin.c
int				execute_builtin_command(t_command *cmd, t_bool is_direct,
					t_shell_env *shell_env);
t_bool			is_builtin(char *command);

/* **************************************************************** */
/*										*/
/*				error					*/
/*										*/
/* **************************************************************** */

// parser_error.c
int				handle_parse_error(t_token_error *e, t_token_list *token,
					t_command *command, t_shell_env *shell_env);
void			set_parse_error(t_token_status status, const char *msg,
					const char *detail, t_token_error *e);

#endif