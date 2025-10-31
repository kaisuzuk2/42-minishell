/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/31 11:03:24 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNS_H
# define EXTERNS_H

# include "command.h"
# include "variables.h"

// tokenize.c
t_token_list	*tokenize(char *line, t_shell_env *shell_env);

// parser.c
t_command		*parser(t_token_list *token, t_shell_env *shell_env);

// parser_error.c
int					handle_parse_error(t_token_error *e, t_token_list *token, t_command *command, t_shell_env *shell_env);
void				set_parse_error(t_token_status status, const char *msg,
						const char *detail, t_token_error *e);

// expand.c
t_bool			expand(t_varlist *env, t_command *command, t_shell_env *shell_env);

// expand_utils.c
t_bool			is_hasdollar(t_word_desc *desc);
t_bool			is_d_quote(t_word_desc *desc);
t_bool			is_s_quote(t_word_desc *desc);
char			*string_quote_removal(char *string, char quote);

// subst.c
char			*expand_string_to_string(t_varlist *env, char *document);

// list.c
size_t			list_length(t_generic_list *list);

// execute_pipeline.c
int				execute_pipeline(t_command *cmd, t_shell_env *env);

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
t_builtin_table	get_builtin_table(void);
int				execute_builtin_command(t_command *cmd,
					const t_builtin *builtin_table, const size_t table_size,
					t_shell_env *env);
t_bool			is_builtin(char *command, const t_builtin *builtin_table,
					const size_t table_size);

// builtin_echo.c
int				builtin_echo(t_word_list *list, t_shell_env *shell_env);

// builtin_env.c
int				builtin_env(t_word_list *list, t_shell_env *shell_env);

// builtin_exit.c
int				builtin_exit(t_word_list *list, t_shell_env *shell_env);

// builtin_export.c
int				builtin_export(t_word_list *list, t_shell_env *shell_env);

// builtin_unset.c
int				builtin_unset(t_word_list *list, t_shell_env *shell_env);

// builtin_pwd.c
int				builtin_pwd(t_word_list *list, t_shell_env *shell_env);

// builtin_cd.c
int				builtin_cd(t_word_list *list, t_shell_env *shell_env);

// variables.c ?? これなんの関数だっけ
t_bool			bind_variable(t_varlist *env, char *key, char *value);

// env_utils.c
char			**get_env_arr(t_varlist *env);
t_shell_var		*list_getshell_var(t_varlist *env, char *key);
char			*list_getenv(t_varlist *env, char *key);
t_bool			update_variable_item(t_varlist *env, char *exportstr);
t_bool			update_key_value(t_varlist *env, char *key, char *value);
char *get_current_working_directory(t_shell_env *shell_env);
t_bool set_current_working_directory(t_shell_env *shell_env, char *value);
void set_last_status(int s, t_shell_env *env);
int get_last_status(t_shell_env *env);

// dispose_env.c
void			dispose_env(t_shell_env *shell_env);
void dispose_shell_var(t_shell_var *var);
void dispose_char_arr(char **arr);

#endif