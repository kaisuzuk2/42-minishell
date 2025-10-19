/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 11:26:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/18 14:38:14 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int builtin_printenv(void)
{
	
}

int builtin_env(t_word_list *list)
{
	if (list)
		return (99); // ### TODO: エラー処理
	return (builtin_printenv());
}