/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:32:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/26 10:44:03 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word_desc	*tokendup(t_word_desc *desc)
{
	t_word_desc	*new;

	new = (t_word_desc *)xmalloc(sizeof(t_word_desc));
	if (!new)
		return (NULL);
	new->word = ft_strdup(desc->word);
	if (!new->word)
		return (free(new), NULL);
	new->kind = desc->kind;
	new->flag = desc->flag;
	return (new);
}

t_command	*new_command(t_command_type type)
{
	t_command	*command;

	command = (t_command *)xcalloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->type = type;
	return (command);
}
