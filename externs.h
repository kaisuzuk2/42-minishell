/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/28 18:42:59 by kaisuzuk         ###   ########.fr       */
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

// builtin_export.c
int				builtin_export(t_word_list *list, t_shell_env *shell_env);

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
t_bool			add_variable_item(t_varlist *env, char *exportstr);

// dispose_env.c
void			dispose_env(t_shell_env *shell_env);

#endif