/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:42:24 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/23 09:35:37 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERROR_STR "cannnot allocate"
# define SYNTAX_ERROR_STR "syntax error"
# define NOT_SUPPORTED_STR "not supported operator"

void fatal_error(char *func, char *str);
void parser_error(char *str);
void parser_operator_error(char *str, char *op);

#endif