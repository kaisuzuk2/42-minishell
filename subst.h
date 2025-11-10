/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:32:32 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/10 13:59:33 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBST_H
# define SUBST_H

// subst.c
char	*expand_string_to_string(char *document, t_shell_env *shell_env);

// subst_getter.c
char	*get_varvalue(t_shell_env *shell_env, char *doll_ptr);
int	get_varlen(char *str);
char	*get_special_value(t_shell_env *shell_env, char *s);
static t_bool	is_special_parameters(char c);

#endif