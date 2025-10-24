/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:48:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/24 10:51:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize_utils.c
void	skip_shellbrank(char **line);
void	set_token_flg(char *line, t_word_desc *desc);
t_bool	startswith(const char *s, const char *op);

// tokenize_utils_tokenkinds.c
t_bool	is_shellbrank(char c);
t_bool	is_word(char *line);
char	*is_metacharacter(char c);
t_bool	is_operator(char *line);
t_bool is_quote(char c);

static t_word_desc	*make_token(char **line, size_t len, t_token_kind kind)
{
	t_word_desc	*desc;
	char		*word;

	desc = (t_word_desc *)xcalloc(sizeof(t_word_desc), 1);
	if (!desc)
		return (NULL);
	desc->flag = W_NOEXPAND;
	if (!line)
		word = NULL;
	else
	{
		set_token_flg(*line, desc);
		word = (char *)xmalloc(sizeof(char) * (len + 1));
		if (!word)
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

	static char *const operators[] = {"<<", "<", ">>", ">", "|"};
	static char *const unsupport_operators[] = {"&&", "&", "||", ";;", ";", "<>" , "<<-" , "<&", ">|",">&", "(", ")"};
	i = 0;
	while (i < sizeof(unsupport_operators) / sizeof(unsupport_operators[0]))
	{
		if (!startswith(*line, unsupport_operators[i]))
		{
			parser_operator_error(NOT_SUPPORTED_STR, unsupport_operators[i]);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!startswith(*line, operators[i]))
			return (make_token(line, ft_strlen(operators[i]),
					operators_table[i]));
		i++;
	}
	return (NULL);
}

static t_word_desc	*make_word_token(char **line)
{
	size_t	len;
	char	quote;

	quote = 0;
	len = 0;
	if (is_quote((*line)[len]))
		quote = (*line)[len++];
	while ((*line)[len])
	{
		if (quote && (*line)[len] == quote)
			quote = 0;
		else if (!quote && is_quote((*line)[len]))
			quote = (*line)[len];
		if (!quote && (is_shellbrank((*line)[len]) || is_metacharacter((*line)[len])))
			break;
		len++;
	}
	if (quote)
		return (parser_error(SYNTAX_ERROR_STR), NULL);
	return (make_token(line, len, TK_WORD));
}

t_token_list	*make_word_list(t_token_list *cur, t_word_desc *desc)
{
	t_token_list	*new;

	if (!desc)
		return (NULL);
	new = (t_token_list *)xcalloc(sizeof(t_token_list), 1);
	if (!new)
		return (NULL);
	new->word = desc;
	cur->next = new;
	return (new);
}

t_token_list	*tokenize(char *line)
{
	t_token_list	head;
	t_token_list	*cur;
	t_token_list	*eof;
	t_word_desc *token;

	head.next = NULL;
	cur = &head;
	token = NULL;
	while (*line)
	{
		if (is_shellbrank(*line))
		{
			skip_shellbrank(&line);
			if (!(*line))
				break;
		}
		if (*line == '#')
			return (head.next);
		else if (is_word(line))
			token = make_word_token(&line);
		else if (is_operator(line))
			token = make_operator_token(&line);
		if (!token)
			return (dispose_token_words(head.next), NULL);
		cur = make_word_list(cur, token);
		if (!cur)
			return (dispose_word(token), dispose_token_words(head.next), NULL);
	}
	cur = make_word_list(cur, make_token(NULL, 0, TK_EOF));
	if (!cur)
		return (dispose_token_words(head.next), NULL);
	return (head.next);
}
