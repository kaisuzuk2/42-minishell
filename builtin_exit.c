/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:22:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/30 12:57:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool is_option(char *opt, char c)
{
	return (opt[0] == '-' && opt[2] == '\0' && opt[1] == c);
}

static int valid_number(char *string)
{
	intmax_t value;
	char *ep;

	value = ft_strtoimax(string, &ep, 10);
}

static int get_exitstat(t_word_list *list)
{

}

static int exit_or_logout(t_word_list *list, t_shell_env *shell_env)
{
	char *arg;

	if (!list)
		return (shell_env->last_status);
	if (list && list->word->word && is_option(list->word->word, '-'))
		list = list->next;
	if (!list)
		return (shell_env->last_status);
	arg = list->word->word;
	if (!)
}

int builtin_exit(t_word_list *list, t_shell_env *shell_env)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (exit_or_logout(list));
}