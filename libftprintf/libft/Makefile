# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suzukikaisei <suzukikaisei@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 09:40:16 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/09/12 13:09:57 by suzukikaise      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc 
FLAG = -Wall -Werror -Wextra -Iincludes
SRCS =	ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c\
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
				ft_strreverse.c \
				ft_putnbr.c \
				ft_putstr.c \
				ft_putchar.c \
				ft_utoa.c \
				ft_strcmp.c \
				ft_isspace.c
B_SRCS=	ft_lstnew.c \
	 ft_lstadd_front.c \
	 ft_lstsize.c \
	 ft_lstlast.c \
	 ft_lstadd_back.c \
	 ft_lstdelone.c \
	 ft_lstclear.c \
	 ft_lstiter.c \
	 ft_lstmap.c
OBJS = $(SRCS:%.c=%.o)
BOBJS = $(B_SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus: $(NAME) $(BOBJS)
	ar -rcs $(NAME) $(BOBJS)
	
%.o: %.c
	$(CC) -c $(FLAG) $< -o $@

clean: 
	rm -rf $(OBJS)
	rm -rf $(BOBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:  clean fclean bonus re