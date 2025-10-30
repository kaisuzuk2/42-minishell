/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/30 17:26:54 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize_utils.c
void				skip_shellbrank(char **line);
void				set_token_flg(char *line, t_word_desc *desc);
t_bool				startswith(const char *s, const char *op);
t_word_desc	*make_token(char **line, size_t len, t_token_kind kind,
						t_token_error *e);
t_token_list		*make_word_list(t_token_list *cur, t_word_desc *desc,
						t_token_error *e);

// tokenize_utils_tokenkinds.c
t_bool				is_shellbrank(char c);
t_bool				is_word(char *line);
char				*is_metacharacter(char c);
t_bool				is_operator(char *line);
t_bool				is_quote(char c);

static t_word_desc	*make_operator_token(char **line_p, char *line,
		t_token_error *e)
{
	int					i;
	const t_token_kind	operators_table[] = {TK_LESS_LESS, TK_LESS,
			TK_GREAT_GREAT, TK_GREAT, TK_PIPE};
	const char			*operators[] = {"<<", "<", ">>", ">", "|"};
	const char			*unsupport_operators[] = {"&&", "&", "||", ";;", ";",
					"<>", "<<-", "<&", ">|", ">&", "(", ")"};

	i = 0;
	while (i < sizeof(unsupport_operators) / sizeof(unsupport_operators[0]))
	{
		if (!startswith(line, unsupport_operators[i]))
			return (e->status = ST_ERR_SYNTAX, e->msg = NOSUP_STR,
				e->detail = unsupport_operators[i], NULL);
		i++;
	}
	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!startswith(line, operators[i]))
			return ((make_token(line_p, ft_strlen(operators[i]),
						operators_table[i], e)));
		i++;
	}
	return (e->status = ST_ERR_SYNTAX, NULL);
}

static t_word_desc	*make_word_token(char **line_p, char *line,
		t_token_error *e)
{
	size_t	len;
	char	quote;

	quote = 0;
	len = 0;
	if (is_quote(line[len]))
		quote = line[len++];
	while (line[len])
	{
		if (quote && line[len] == quote)
			quote = 0;
		else if (!quote && is_quote(line[len]))
			quote = line[len];
		if (!quote && (is_shellbrank(line[len]) || is_metacharacter(line[len])))
			break ;
		len++;
	}
	if (quote)
	{
		return (e->status = ST_ERR_SYNTAX, e->msg = SYNTAX_ERR_STR,
			e->detail = QUOTE_ERR_STR, NULL);
	}
	return (make_token(line_p, len, TK_WORD, e));
}

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
	if (!list)
		return (e->status = ST_ERR_NOMEM, NULL);
	return (list);
}

t_token_list	*append_token(char *line, t_shell_env *shell_env)
{
	t_token_list	head;
	t_token_list	*cur;
	t_token_error	e;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		memset(&e, 0, sizeof(e));
		if (is_shellbrank(*line))
			skip_shellbrank(&line);
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
	eof = make_token(NULL, 0, TK_EOF, &e);
	if (!eof)
	{
		dispose_token_words(list);
		dispose_env(shell_env);
		exit(1);
	}
	t = list;
	while (t->next)
		t = t->next;
	t = make_word_list(t, eof, &e);
	if (!t)
	{
		dispose_token_words(list);
		dispose_env(shell_env);
		exit(1);
	}
	return (list);
}
