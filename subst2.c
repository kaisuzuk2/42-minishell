/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:35:11 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/10 09:42:16 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_exp_kind 
{
	EXP_TEXT,
	EXP_SQ,
	EXP_DQ,
	EXP_VAR
} t_exp_kind;

typedef struct s_exp_token
{
	struct s_exp_token *next;
	char *word;
	t_exp_kind kind;
} t_exp_token;



t_bool expand_string_with_quote(t_word_list **list_p, t_word_list *list, t_shell_env *shell_env)
{

}