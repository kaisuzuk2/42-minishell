# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 16:23:46 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/07/05 19:30:44 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
MAKE	=	make -C
CC		=	cc -Wall -Werror -Wextra -Iincludes
INC		=	-Iincludes

FT_NAME	=	libft
INC		+=	-Ilibft

_SRCS	=	ft_dprintf.c \
			ft_dprintf_p.c\
			ft_dprintf_u.c\
			ft_dprintf_x.c \
			ft_dprintf_c.c
		
_BSRCS	=	ft_printf_bonus.c \
			ft_printf_set_flg_prec_bonus.c \
			ft_printf_set_utils_bonus.c \
			ft_printf_di_bonus.c  \
			ft_printf_c_bonus.c \
			ft_printf_s_bonus.c \
			ft_printf_u_bonus.c \
			ft_printf_p_bonus.c \
			ft_printf_x_bonus.c \
			ft_putnchar_bonus.c
		
SRCS = $(patsubst %, srcs/%, $(_SRCS))
BSRCS = $(patsubst %, bonus/%, $(_BSRCS))
OBJS = $(SRCS:%.c=%.o)
BOBJS = $(BSRCS:%.c=%.o)

all: $(NAME)
	
$(NAME): $(OBJS) $(FT_NAME).a
	cp $(FT_NAME)/$(FT_NAME).a $(NAME)
	ar rcs $(NAME) $(OBJS)

bonus : $(BOBJS)
	$(MAKE) ./libft fclean
	$(MAKE) ./libft
	cp libft/libft.a $(NAME)
	ar rcs $(NAME) $(BOBJS)

%.o: %.c
	$(CC) $(INC) -c -o $@  $<

$(FT_NAME).a: 
	$(MAKE) libft

clean :
	$(MAKE) ./libft clean
	rm -rf $(OBJS)
	rm -rf $(BOBJS)

fclean : clean
	$(MAKE) ./libft fclean
	rm -rf $(NAME)

re : clean fclean all

.PHONY: clean fclean bonus all
	