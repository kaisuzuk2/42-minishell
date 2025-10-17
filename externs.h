/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/17 08:06:43 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNS_H
# define EXTERNS_H

# include "command.h"

// tokenize.c
t_token_list	*tokenize(char *line);

// parser.c
t_command		*parser(t_token_list *token);

// expand.c
t_bool			expand(t_command *command);

// list.c
size_t			list_length(t_generic_list *list);

// execute_pipeline.c
int execute_pipeline(t_command *cmd);

// findcmd.c
char	*search_for_command(char *cmd);

// strvec.c
char	**strvec_from_word_list(t_word_list *list);

#endif