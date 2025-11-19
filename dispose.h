/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:04:33 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 09:53:20 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPOSE_CMD_H
# define DISPOSE_CMD_H

# include "command.h"

void	dispose_word(t_word_desc *w);
void	dispose_token_words(t_token_list *list);
void	dispose_desc_words(t_word_list *list);
void	dispose_redirects(t_redirect *list);
void	dispose_command(t_command *command);
void	dispose_simple_command(t_command *command);

#endif