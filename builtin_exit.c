/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:22:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/01 09:28:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_strtoimax.c
intmax_t		ft_strtoimax(const char *nptr, char **endptr);

static t_bool	is_option(char *opt, char c)
{
	return (opt[0] == '-' && opt[2] == '\0' && opt[1] == c);
}

static intmax_t	valid_number(char *string)
{
	char			*ep;
	const intmax_t	value = ft_strtoimax(string, &ep);

	while (ft_isspace((unsigned char)*ep))
		ep++;
	if (*ep != '\0')
		return (builtin_error("exit", string, EXIT_ERR_STR), -1);
	return (value);
}

static int	get_exitstat(t_word_list *list)
{
	const intmax_t value = valid_number(list->word->word);
	if (value < 0)
		return (value);
	return (value & 255);
}

static int	exit_or_logout(t_word_list *list, t_shell_env *shell_env)
{
	char	*arg;
	int status;

	if (!list)
		return (shell_env->last_status);
	if (list && list->word->word && is_option(list->word->word, '-'))
		list = list->next;
	if (!list)
		return (shell_env->last_status);
	status = get_exitstat(list);
	if (status < 0)
		return (2);
	if (list->next)
		return (builtin_error("exit", NULL, ARGNUM_ERR_STR), 256);
	return (get_exitstat(list));
}

int	builtin_exit(t_word_list *list, t_shell_env *shell_env)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (exit_or_logout(list, shell_env));
}