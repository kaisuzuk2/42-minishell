/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/10 11:42:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNS_H
# define EXTERNS_H

#include "command.h"

// tokenize.c
t_token_list *tokenize(char *line);

// parser.c
t_command	*parser(t_token_list *token);

#endif