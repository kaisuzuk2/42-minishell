/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 09:40:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/12 18:18:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ### TODO: ポインタじゃないほうがいいのでは
// int	handle_parse_error(t_token_error *e, t_token_list *token,
// 		t_command *command, t_shell_env *shell_env)
// {
// 	if (e->status == ST_OK)
// 		return (0);
// 	dispose_token_words(token);
// 	dispose_command(command);
// 	if (e->status == ST_ERR_NOMEM)
// 	{
// 		dispose_env(shell_env);
// 		exit(EX_FATAL_ERROR);
// 	}
// 	if (e->status == ST_ERR_SYNTAX)
// 		parser_operator_error(e->msg, e->detail);
// 	else if (e->status == ST_SIGNAL)
// 		set_last_status(130, shell_env);
// 	else
// 		set_last_status(EX_SYNTAX_ERROR, shell_env);
// 	return (1);
// }

int	handle_parse_error(t_token_error *e, t_token_list *token,
		t_command *command, t_shell_env *shell_env)
{
	if (e->status == ST_OK)
		return (0);
	dispose_token_words(token);
	dispose_command(command);
	if (e->status == ST_ERR_NOMEM)
	{
		dispose_env(shell_env);
		exit(EX_FATAL_ERROR);
	}
	if (e->status == ST_ERR_SYNTAX)
		parser_operator_error(e->msg, e->detail);
	if (e->status == ST_SIGNAL)
		set_last_status(130, shell_env);
	else
		set_last_status(EX_SYNTAX_ERROR, shell_env);
	return (1);
}

void	set_parse_error(t_token_status status, const char *msg,
		const char *detail, t_token_error *e)
{
	e->status = status;
	e->msg = msg;
	e->detail = detail;
}
