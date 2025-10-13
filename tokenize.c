/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/13 11:33:42 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_shellbrank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static void	skip_shellbrank(char **line)
{
	while (**line && is_shellbrank(**line))
	{
		(*line)++;
	}
}

static char	*is_metacharacter(char c)
{
	// ### TODO: メタ文字これでいいか再検討
	return (ft_strchr("*?~#\\$!;|&<>(){}", c));
}

static t_bool	startswith(const char *s, const char *op)
{
	return (ft_strncmp(s, op, ft_strlen(op)));
}

static t_bool	is_operator(char *line)
{
	int	i;

	// ### TODO: オペレーターこれでいいか再検討
	static char *const operators[] = {"<<", "<", ">>", ">", "|"};
	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!startswith(line, operators[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void set_token_flg(char *line, t_word_desc *desc)
{
	if (*line == '\'')
		desc->flag = W_SQUOTE;
	else if (*line == '\"')
		desc->flag = W_DQUOTE;
	else if (*line == '$')
		desc->flag = W_HASDOLLAR;
	else 
		desc->flag = W_NOEXPAND;
}

static t_word_desc	*make_token(char **line, size_t len, t_token_kind kind)
{
	t_word_desc	*desc;
	char		*word;

	desc = (t_word_desc *)ft_calloc(sizeof(t_word_desc), 1);
	if (!desc) // ### TODO: エラー処理
		return (NULL);
	if (!line)
		word = NULL;
	else
	{
		set_token_flg(*line, desc);
		word = (char *)malloc(sizeof(char) * (len + 1));
		if (!word) // ### TODO: エラー処理
			return (free(desc), NULL);
		ft_memcpy(word, *line, len);
		word[len] = '\0';
		*line += len;
	}
	desc->word = word;
	desc->kind = kind;
	return (desc);
}

static t_word_desc	*make_operator_token(char **line)
{
	static int const	operators_table[] = {TK_LESS_LESS, TK_LESS,
			TK_GREAT_GREAT, TK_GREAT, TK_PIPE};
	int					i;
	t_word_desc			*desc;

	// ### TODO: オペレーター追加する
	static char *const operators[] = {"<<", "<", ">>", ">", "|"};
	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!startswith(*line, operators[i]))
			return (make_token(line, ft_strlen(operators[i]),
					operators_table[i]));
		i++;
	}
	free(desc);
	return (NULL);
}

static t_bool	is_word(char *line)
{
	return (*line && !is_metacharacter(*line));
}

// FAIL		:		NULL
// SUCCESS	:		pointer
static t_word_desc	*make_word_token(char **line)
{
	size_t	len;
	int		quote_flg;
	char	quote;

	quote = 0;
	len = 0;
	if ((*line)[len] == '\'' || (*line)[len] == '\"')
	{
		quote_flg = 1;
		quote = (*line)[len];
		len++;
	}
	while ((*line)[len] && !is_shellbrank((*line)[len])
		&& !is_metacharacter((*line)[len]))
	{
		while ((*line)[len] && quote_flg)
		{
			if ((*line)[len] == quote)
			{
				quote_flg = !quote_flg;
				break ;
			}
			len++;
		}
		len++;
	}
	if (quote)
		printf("### Quote error\n"); // ### TODO: エラー処理
	return (make_token(line, len, TK_WORD));
}

t_token_list	*make_word_list(t_token_list *cur, t_word_desc *desc)
{
	t_token_list	*new;

	if (!desc)
		return (NULL);
	new = (t_token_list *)ft_calloc(sizeof(t_token_list), 1);
	if (!new)
		return (NULL);
	new->word = desc;
	cur->next = new;
	return (new);
}

// FAIL		:		NULL
// SUCCESS	:		t_token_list pointer
t_token_list	*tokenize(char *line)
{
	t_token_list	head;
	t_token_list	*cur;
	t_token_list	*eof;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		if (is_shellbrank(*line))
			skip_shellbrank(&line);
		else if (is_word(line))
			cur = make_word_list(cur, make_word_token(&line));
		else if (is_operator(line))
			cur = make_word_list(cur, make_operator_token(&line));
		else
			printf("### Error\n");
		if (!cur)
			return (dispose_token_words(&head), NULL);
	}
	cur = make_word_list(cur, make_token(NULL, 0, TK_EOF));
	return (head.next);
}
