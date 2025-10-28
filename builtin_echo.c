/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 07:58:42 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/27 17:57:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Options:
  -n	do not append a newline
*/

#include "minishell.h"

#define VALID_ECHO_OPTIONS "n"

static t_bool	is_option(t_word_list **list_p, t_word_list *list)
{
	int		i;
	char	*tmp;
	t_bool	display_return ;

	display_return = TRUE;
	while (list)
	{
		*list_p = list;
		tmp = list->word->word;
		if (!tmp || *tmp != '-')
			break ;
		tmp++;
		i = 0;
		while (tmp[i])
		{
			if (ft_strchr(VALID_ECHO_OPTIONS, tmp[i]) == 0)
				break ;
			i++;
		}
		if (*tmp == 0 || tmp[i])
			break ;
		display_return = FALSE;
		list = list->next;
	}
	return (display_return);
}

int	builtin_echo(t_word_list *list, t_varlist *env)
{
	const t_bool	display_return = is_option(&list, list);

	while (list)
	{
		ft_dprintf(STDOUT_FILENO, list->word->word);
		list = list->next;
		if (list)
			ft_putchar(' ');
	}
	if (display_return)
		ft_putchar('\n');
	return (EXECUTION_SUCCESS);
}
