/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:42:24 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/22 16:07:21 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERROR_STR "cannnot allocate"

void fatal_error(char *func, char *str);
void parser_error(char *str);

#endif