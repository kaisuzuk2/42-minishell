/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 23:47:02 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/05/09 17:14:45 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef int		t_bool;

# define TRUE 1
# define FALSE 0

# define PERROR "(nil)"
# define SERROR "(null)"
# define SIGN_SIZE 1
# define SHARP_SIZE 2

typedef struct s_flg
{
	t_bool		ladjust;
	t_bool		prec;
	t_bool		sharp;
	t_bool		sign;
	size_t		field_width;
	size_t		prec_width;
	int			padc;
	t_bool		is_string;
	const char	*sharp_ox;
}				t_flg;

typedef struct s_utils
{
	size_t		act_len;
	size_t		field_pad;
	size_t		prec_pad;
	size_t		total_len;
}				t_utils;

int				ft_printf(const char *format, ...);
int				ft_printf_di(int n, t_flg *flg);
int				ft_printf_c(int c, t_flg *flg);
int				ft_printf_s(const char *str, t_flg *flg);
int				ft_printf_u(unsigned int un, t_flg *flg);
int				ft_printf_p(void *p, t_flg *flg);
int				ft_printf_x(unsigned int un, t_flg *flg, int capital);
void			ft_printf_set_flg_prec(const char **fmt, t_flg *flg);
void			ft_printf_set_utils(const char *strn, t_flg *flg, t_utils *utl);

int				ft_putstr(const char *str);
int				ft_putnbr(int n);
int				ft_putchar(char c);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
int				ft_putnchar(int c, int size);

#endif