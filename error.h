/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:42:24 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/27 13:21:31 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERR_STR "cannnot allocate"
# define SYNTAX_ERR_STR "syntax error"
# define QUOTE_ERR_STR "unclosed quote"
# define NOSUP_STR "not supported operator"
# define PARSE_ERR_STR "syntax error near unexpected token"
# define BUILTIN_ERR_STR "internal error: builtin function is NULL pointer"
# define NOTFOUND_STR "command not found"

void fatal_error(char *func, char *str);
void parser_error(char *str);
void parser_operator_error(const char *msg, const char *detail);
void internal_error(const char *msg, const char *detail);
void	sys_error(char *err_txt);

#endif