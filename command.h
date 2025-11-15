/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:53:00 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 17:47:22 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

/* Possible values for the `flags' field of a WORD_DESC. */
// ### TODO: フラグの内容を精査する　使いすべきものを確認する
# define W_SQUOTE 0x01
# define W_DQUOTE 0x02
# define W_HASDOLLAR 0x04

typedef struct s_glist
{
	struct s_glist		*next;
}						t_generic_list;

/* **************************************************************** */
/*										*/
/*			Token Structs					*/
/*										*/
/* **************************************************************** */

// local errno
typedef enum e_token_status
{
	ST_OK,
	ST_ERR_SYNTAX,
	ST_ERR_NOMEM,
	ST_SIGNAL,
}						t_token_status;

typedef struct s_token_error
{
	t_token_status		status;
	const char			*msg;
	const char			*detail;
}						t_token_error;

typedef enum e_token_kind
{
	TK_WORD,
	TK_GREAT_GREAT,// >>
	TK_GREAT,// >
	TK_LESS_LESS,// <<
	TK_LESS,// <
	TK_PIPE,
	TK_SYNTAX_ERR,
	TK_EOF,
}						t_token_kind;

typedef struct s_word_desc
{
	t_token_kind		kind;
	char				*word;
	t_bool				flag;
}						t_word_desc;

typedef struct s_token_list
{
	t_word_desc			*word;
	struct s_token_list	*next;
}						t_token_list;

/* **************************************************************** */
/*										*/
/*			Shell Command Structs					*/
/*										*/
/* **************************************************************** */

typedef enum e_command_type
{
	CM_SIMPLE,
	CM_CONNECTION,
}						t_command_type;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc			*word;
}						t_word_list;

typedef enum e_instruction
{
	r_output_direction,// >
	r_input_direction,// <
	r_appending_to,// >>
	r_reading_until,// <<
}						t_instruction;

// ### TODO: destはfdの複製用のため不要 削除してfilenameだけにする
typedef union u_redirectee
{
	// int					dest;
	t_word_desc			*filename;
}						t_redirectee;

// parser.c set for redirect by table
typedef struct s_redirect_info
{
	t_token_kind		kind;
	t_instruction		instruction;
	int					flag;
}						t_redirect_info;

typedef struct s_redirect
{
	struct s_redirect	*next;
	t_redirectee		redirector;
	int					flags;
	t_instruction		instruction;
	t_redirectee		redirectee;
	char				*here_doc_eof;
}						t_redirect;

typedef struct s_command
{
	struct s_command	*head;
	t_command_type		type;
	// command args : <ls -l> <cat -e>
	struct s_command	*command;
	t_word_list			*words;
	t_redirect			*redirects;
	struct s_command	*next;
}						t_command;

#endif