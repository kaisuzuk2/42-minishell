/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/19 14:12:47 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize_utils.c
void				skip_shellblank(char **line);

// tokenize_make.c
t_word_desc			*make_token(char **line, size_t len, t_token_kind kind,
						t_token_error *e);
t_word_desc			*make_word_token(char **line_p, char *line,
						t_token_error *e);
t_word_desc			*make_operator_token(char **line_p, char *line,
						t_token_error *e);
t_token_list		*make_word_list(t_token_list *cur, t_word_desc *desc,
						t_token_error *e);

static t_token_list	*make_word_list_wrapper(t_token_list *cur, char **line_p,
		char *line, t_token_error *e)
{
	t_word_desc		*token;
	t_token_list	*list;

	if (is_word(line))
		token = make_word_token(line_p, line, e);
	else
		token = make_operator_token(line_p, line, e);
	if (e->status != ST_OK)
		return (NULL);
	list = make_word_list(cur, token, e);
	if (e->status != ST_OK)
		return (NULL);
	return (list);
}

static t_token_list	*append_token(char *line, t_shell_env *shell_env)
{
	t_token_list	head;
	t_token_list	*cur;
	t_token_error	e;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		memset(&e, 0, sizeof(e));
		if (is_shellblank(*line))
			skip_shellblank(&line);
		if (!*line || *line == '#')
			return (head.next);
		cur = make_word_list_wrapper(cur, &line, line, &e);
		if (handle_parse_error(&e, head.next, NULL, shell_env))
			return (NULL);
	}
	return (head.next);
}

t_token_list	*tokenize(char *line, t_shell_env *shell_env)
{
	t_token_list	*list;
	t_token_list	*t;
	t_word_desc		*eof;
	t_token_error	e;

	list = append_token(line, shell_env);
	if (!list)
		return (NULL);
	memset(&e, 0, sizeof(e));
	eof = make_token(NULL, 0, TK_EOF, &e);
	if (handle_parse_error(&e, list, NULL, shell_env))
		return (NULL);
	t = list;
	while (t->next)
		t = t->next;
	memset(&e, 0, sizeof(e));
	make_word_list(t, eof, &e);
	if (handle_parse_error(&e, list, NULL, shell_env))
	{
		dispose_word(eof);
		return (NULL);
	}
	return (list);
}
