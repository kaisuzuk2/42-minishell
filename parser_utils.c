/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:32:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/25 18:06:39 by kaisuzuk         ###   ########.fr       */
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

t_bool	is_redirect(t_token_kind kind)
{
	return (kind == TK_GREAT_GREAT || kind == TK_GREAT || kind == TK_LESS_LESS
		|| kind == TK_LESS);
}

int parse_error(t_token_error *e, t_token_list *token, t_command *command)
{
	if (e->status == ST_OK)
		return (0);
	if (e->status == ST_ERR_SYNTAX)
		parser_operator_error(e->msg, e->detail);
	dispose_token_words(token);
	dispose_command(command);
	if (e->status == ST_ERR_NOMEM)
		exit (1);
	return (1);
}

void set_parse_error(t_token_status status, const char *msg, const char *detail, t_token_error *e)
{
	e->status = status;
	e->msg = msg;
	e->detail = detail;
}