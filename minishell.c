/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:13:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/06 13:17:43 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	
	while (1)
	{
		//TODO:  prompt is $PS1
		line = readline("minishell$ ");

		if (!line)
			break;
		if (*line)
			add_history(line);
		free(line);
	}
}