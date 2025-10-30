/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 09:40:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/30 17:24:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO: ポインタじゃないほうがいいのでは
int	handle_parse_error(t_token_error *e, t_token_list *token, t_command *command, t_shell_env *shell_env)
{
	if (e->status == ST_OK)
		return (0);
	if (e->status == ST_ERR_SYNTAX)
		parser_operator_error(e->msg, e->detail);
	dispose_token_words(token);
	dispose_command(command);
	dispose_env(shell_env);
	if (e->status == ST_ERR_NOMEM)
		exit(1);
	return (1);
}

void	set_parse_error(t_token_status status, const char *msg,
		const char *detail, t_token_error *e)
{
	e->status = status;
	e->msg = msg;
	e->detail = detail;
}