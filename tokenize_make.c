/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_make.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:05:26 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/12/09 11:00:21 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize_utils.c
void			set_token_flg(char *line, t_word_desc *desc);
t_bool			is_match_op(char *str, size_t len, const char *op);

t_word_desc	*make_token(char **line, size_t len, t_token_kind kind,
		t_token_error *e)
{
	t_word_desc	*desc;
	char		*word;

	desc = (t_word_desc *)xcalloc(sizeof(t_word_desc), 1);
	if (!desc)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	desc->flag = 0;
	if (!line)
		word = NULL;
	else
	{
		set_token_flg(*line, desc);
		word = (char *)xmalloc(sizeof(char) * (len + 1));
		if (!word)
			return (free(desc), set_parse_error(ST_ERR_NOMEM, NULL, NULL, e),
				NULL);
		ft_memcpy(word, *line, len);
		word[len] = '\0';
		*line += len;
	}
	desc->word = word;
	desc->kind = kind;
	return (desc);
}

t_word_desc	*make_word_token(char **line_p, char *line, t_token_error *e)
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
		if (!quote && (is_shellblank(line[len]) || is_metacharacter(line[len])))
			break ;
		len++;
	}
	if (quote)
		return (set_parse_error(ST_ERR_SYNTAX, SYNTAX_ERR_STR, QUOTE_ERR_STR,
				e), NULL);
	return (make_token(line_p, len, TK_WORD, e));
}

static t_bool	is_unsup_op(char *line, size_t len, t_token_error *e)
{
	const char	*unsup_op[] = {"&&", "&", "||", ";;", ";", "<>", "<<-", "<&",
		">|", ">&", "(", ")"};
	const int	table_size = sizeof(unsup_op) / sizeof(unsup_op[0]);
	int			i;

	i = 0;
	while (i < table_size)
	{
		if (is_match_op(line, len, unsup_op[i]))
			return (set_parse_error(ST_ERR_SYNTAX, NOSUP_STR, unsup_op[i], e),
				TRUE);
		i++;
	}
	return (FALSE);
}

t_word_desc	*make_operator_token(char **line_p, char *line, t_token_error *e)
{
	unsigned long long int	i;
	size_t					len;
	const t_token_kind		op_table[] = {TK_LESS_LESS, TK_LESS, TK_GREAT_GREAT,
		TK_GREAT, TK_PIPE};
	const char				*op[] = {"<<", "<", ">>", ">", "|"};

	len = 0;
	while (line[len] && is_metacharacter(line[len]))
		len++;
	if (is_unsup_op(line, len, e))
		return (NULL);
	i = 0;
	while (i < sizeof(op) / sizeof(op[0]))
	{
		if (is_match_op(line, len, op[i]))
			return (make_token(line_p, ft_strlen(op[i]), op_table[i], e));
		i++;
	}
	return (make_token(line_p, len, TK_SYNTAX_ERR, e));
}

t_token_list	*make_word_list(t_token_list *cur, t_word_desc *desc,
		t_token_error *e)
{
	t_token_list	*new;

	if (!desc)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	new = (t_token_list *)xcalloc(sizeof(t_token_list), 1);
	if (!new)
		return (dispose_word(desc), set_parse_error(ST_ERR_NOMEM, NULL, NULL,
				e), NULL);
	new->word = desc;
	cur->next = new;
	return (new);
}
