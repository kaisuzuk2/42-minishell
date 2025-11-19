/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:04:33 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 14:14:12 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPOSE_H
# define DISPOSE_H

# include "command.h"
# include "variables.h"

// dispose_cmd.c
void	dispose_simple_command(t_command *command);
void	dispose_command(t_command *command);

// dispose_token.c
void	dispose_word(t_word_desc *w);
void	dispose_token_words(t_token_list *list);
void	dispose_desc_words(t_word_list *list);

// dispose_env.c
void	dispose_env(t_shell_env *shell_env);
void	dispose_varlist(t_varlist *list);
void	dispose_shell_var(t_shell_var *var);
void	dispose_char_arr(char **arr);

#endif