/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:22:32 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/06 14:40:25 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_dprintf_p(int fd, void *p);
int	ft_dprintf_u(int fd, unsigned int un);
int	ft_dprintf_x(int fd, unsigned int un, unsigned int capital);
int	ft_dprintf(int fd, const char *format, ...);
int	ft_dprintf_c(int fd, int c);

#endif