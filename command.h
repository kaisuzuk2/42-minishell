/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:52:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/09/11 14:57:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

/* **************************************************************** */
/*								    */
/*			lex structure    */
/*								    */
/* **************************************************************** */

/* A structure which represents a word. */
typedef struct word_desc
{
	char *wordl;	/* Zero terminated string. */
	int flags;		/* Flags associated with this word. */
} t_word_desc;

/* A linked list of words. */
typedef struct word_list
{
	struct word_list *next;
	t_word_desc *word;
} t_word_list;

#endif