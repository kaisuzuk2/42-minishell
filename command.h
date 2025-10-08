/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:53:00 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/08 14:04:43 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

/* **************************************************************** */
/*								    */
/*			Token Structs			    */
/*								    */
/* **************************************************************** */

typedef enum e_token_kind
{
	TK_WORD, 
	TK_GREAT_GREAT,
	TK_GREAT,
	TK_LESS_LESS,
	TK_LESS,
	TK_PIPE,
	TK_EOF,
} t_token_kind;

typedef struct s_word_desc
{
	t_token_kind kind;
	char *word;
	int flag;
} t_word_desc;

typedef struct s_token_list 
{
	t_word_desc *word;
	struct s_token_list *next;
} t_token_list;


/* **************************************************************** */
/*								    */
/*			Shell Command Structs			    */
/*								    */
/* **************************************************************** */

typedef enum e_command_type
{
	CM_SIMPLE
} t_command_type;

typedef struct s_word_list
{
	struct s_word_list *next;
	t_word_desc *word;
} t_word_list; 

typedef struct s_command 
{
	struct s_command *next;
	t_command_type type;
	t_word_list *words;
	
} t_command;

#endif