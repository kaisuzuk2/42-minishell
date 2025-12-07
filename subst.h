/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:32:32 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/12/07 13:57:32 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBST_H
# define SUBST_H

// subst.c
char	*expand_tilda(char *res, char **document, t_varlist *env);
char	*expand_string_to_string(char *document, char *document_ptr,
			t_shell_env *shell_env);

// subst_get.c
char	*get_varvalue(t_shell_env *shell_env, char *doll_ptr);
int		get_varlen(char *str);
char	*get_special_value(t_shell_env *shell_env, char *s);
t_bool	is_special_parameters(char c);

#endif