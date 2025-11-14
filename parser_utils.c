/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:32:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/14 10:36:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parser_utils_tokenkind.c
t_bool				is_wordtoken(t_token_kind kind);
t_bool				is_eoftoken(t_token_kind kind);
t_bool				is_redirect(t_token_kind kind);
t_bool				is_pipetoken(t_token_kind kind);

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

// unexpected = [ command | | command ] or [command |<EOF>]
t_bool is_unexpected_token(t_command *cmd, t_token_list *token)
{
	if (!cmd->command && !is_wordtoken(token->word->kind) && !is_redirect(token->word->kind))
		return (TRUE);
	if (is_pipetoken(token->word->kind && is_eoftoken(token->next->word->kind)))
		return (TRUE);
	return (FALSE);
}