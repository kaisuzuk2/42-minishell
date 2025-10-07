/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/07 15:23:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static t_bool is_shellbrank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static void skip_shellbrank(char **line)
{
	while (**line && is_shellbrank(**line))
	{
		(*line)++;
	}
}

static char *is_metacharacter(char c)
{
	// ### TODO: メタ文字これでいいか再検討
	return (ft_strchr("*?~#\\$!;|&<>(){}", c));
}

static t_bool is_operator(char *line)
{
	// ### TODO: オペレーターこれでいいか再検討
	static char *const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t op_len;
	int i;

	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		op_len = ft_strlen(operators[i]);
		if (ft_strncmp(line, op[i], len))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static t_word_desc *make_operator_token(char **line)
{
	size_t len;
	t_word_desc *desc;
	char *word;
	char *line_p;

	line_p = *line;
	desc = (t_word_desc *)malloc(sizeof(t_word_desc));
	if (!desc)
		return (NULL);
	len = 0;
}

static t_bool is_word(char *line)
{
	const char *operators[] = {">>", ">", "<<", "<", "|"};
	return (*line && !is_metacharacter(*line));
}

// FAIL		:		NULL
// SUCCESS	:		pointer
static t_word_desc *make_word_token(char **line)
{
	size_t len;
	t_word_desc *desc;
	char *word;
	char *line_p;

	line_p = *line;
	desc = (t_word_desc *)malloc(sizeof(t_word_desc));
	if (!desc)
		return (NULL);
	len = 0;
	while (**line && !is_shellbrank(**line) && !is_metacharacter(**line))
	{
		(*line)++;
		len++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (free(desc), NULL);
	ft_memcpy(word, line_p, len);
	word[len] = '\0';
	desc->word = word;
	return (desc);
}

t_token_list *make_word_list(t_token_list *cur, t_word_desc *desc)
{
	t_token_list *new;

	if (!desc)
		return (NULL);
	new = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->word = desc;
	cur->next = new;
	return (new);
}

// FAIL		:		NULL
// SUCCESS	:		t_token_list pointer
t_token_list *tokenize(char *line)
{
	t_token_list head;
	t_token_list *cur;
	t_token_list *new;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		skip_shellbrank(&line);
		if (is_word(line))
			cur = make_word_list(cur, make_word_token(&line));
	}
	return (head.next);
}