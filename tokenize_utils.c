/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:39:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/31 09:29:15 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize_utils_tokenkinds.c
t_bool				is_shellbrank(char c);

void	skip_shellbrank(char **line)
{
	while (**line && is_shellbrank(**line))
		(*line)++;
}

void	set_token_flg(char *line, t_word_desc *desc)
{
	if (ft_strchr(line, '$'))
		desc->flag = W_HASDOLLAR;
	if (*line == '\'')
		desc->flag = W_SQUOTE;
	else if (*line == '\"')
		desc->flag = W_DQUOTE;
}

t_bool	startswith(const char *s, const char *op)
{
	return (ft_strncmp(s, op, ft_strlen(op)));
}

t_word_desc	*make_token(char **line, size_t len, t_token_kind kind,
		t_token_error *e)
{
	t_word_desc	*desc;
	char		*word;

	desc = (t_word_desc *)xcalloc(sizeof(t_word_desc), 1);
	if (!desc)
		return (set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	desc->flag = W_NOEXPAND;
	if (!line)
		word = NULL;
	else
	{
		set_token_flg(*line, desc);
		word = (char *)xmalloc(sizeof(char) * (len + 1));
		if (!word)
			return (free(desc), set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
		ft_memcpy(word, *line, len);
		word[len] = '\0';
		*line += len;
	}
	desc->word = word;
	desc->kind = kind;
	return (desc);
}

t_token_list	*make_word_list(t_token_list *cur, t_word_desc *desc,
		t_token_error *e)
{
	t_token_list	*new;

	if (!desc)
		return (NULL);
	new = (t_token_list *)xcalloc(sizeof(t_token_list), 1);
	if (!new)
		return (dispose_word(desc), set_parse_error(ST_ERR_NOMEM, NULL, NULL, e), NULL);
	new->word = desc;
	cur->next = new;
	return (new);
}
