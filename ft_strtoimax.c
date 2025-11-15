/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoimax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:56:01 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/15 17:26:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_space(const unsigned char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

static t_bool	is_negative(const unsigned char **str)
{
	t_bool	res;

	res = FALSE;
	if (**str == '+' || **str == '-')
	{
		res = (**str == '-');
		(*str)++;
	}
	return (res);
}

static void	set_overflow_num(intmax_t *cutoff, intmax_t *cutlim,
		t_bool negative)
{
	if (negative)
	{
		*cutoff = INTMAX_MIN / 10;
		*cutlim = INTMAX_MIN % 10;
	}
	else
	{
		*cutoff = -(INTMAX_MAX / 10);
		*cutlim = -(INTMAX_MAX % 10);
	}
}

intmax_t	ft_strtoimax(const char *nptr, char **endptr)
{
	const unsigned char	*s = (const unsigned char *)nptr;
	t_bool				negative;
	intmax_t			cutoff;
	intmax_t			cutlim;
	intmax_t			res;

	skip_space(&s);
	negative = is_negative(&s);
	set_overflow_num(&cutoff, &cutlim, negative);
	res = 0;
	while (ft_isdigit(*s))
	{
		if (res < cutoff || (res == cutoff && -((*s) - '0') < cutlim))
			break ;
		res = res * 10 - ((*s) - '0');
		s++;
	}
	if (!negative)
		res = -res;
	if (!res && *nptr != '0')
		*endptr = (char *)nptr;
	else
		*endptr = (char *)s;
	return (res);
}
