/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/19 09:20:04 by kaisuzuk         ###   ########.fr       */
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
t_bool			expand(t_command *command);
char			*expand_string_to_string(char *document);

// list.c
size_t			list_length(t_generic_list *list);

// execute_pipeline.c
int				execute_pipeline(t_command *cmd);

// findcmd.c
char			*search_for_command(char *cmd);
char			*savestring(char *str);

// strvec.c
char			**strvec_from_word_list(t_word_list *list);

// ft_mkstmp
int				ft_mkstemp(char **template);

// redir.c
int				do_redirections(t_redirect *redirect);

// make_cmd.c
char			*make_here_document(t_redirect *r);

// builtin.c
t_builtin_func	*find_shell_builtin(const char *name);

// builtin_echo.c
int				builtin_echo(t_word_list *list);

// variables.c
t_varlist		*initialize_shell_variables(char **envp);

#endif