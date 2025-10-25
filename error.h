/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:42:24 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/25 12:51:58 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERROR_STR "cannnot allocate"
# define SYNTAX_ERROR_STR "syntax error"
# define QUOTE_ERROR_STR "unclosed quote"
# define NOT_SUPPORTED_STR "not supported operator"
# define PARSE_ERROR_STR "syntax error near unexpected token"

void fatal_error(char *func, char *str);
void parser_error(char *str);
void parser_operator_error(const char *msg, const char *detail);

#endif