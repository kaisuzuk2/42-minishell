/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:56:10 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/20 10:59:51 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_pwd(t_word_list *list, t_varlist *env)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (99); // ###TODO: エラー処理
	printf("%s\n", pwd);
	return (1);
}