# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/10 15:36:18 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/09/10 17:07:50 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	cc
FLAG	=	-Wall -Werror -Wextra
INC		=	-Iincludes 

MAKE	=	make -C
RM		=	rm -rf

FT_NAME	=	libftprintf
FT_URL	=	https://github.com/kaisuzuk2/ft_dprintf.git
INC		+=	-I$(FT_NAME)/includes
INC		+=	-I$(FT_NAME)/libft

SRCS	=	minishell.c \
			execute_cmd.c \
			findcmd.c 

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FT_NAME) $(OBJS)
	$(MAKE) $(FT_NAME)
	$(CC) -o $(NAME) $(INC) $(OBJS) -lreadline -L$(FT_NAME) -lftprintf

%.o: %.c
	$(CC) -c  $(INC) $< -o $@

$(FT_NAME): 
	git clone $(FT_URL) $(FT_NAME)

clean:
	$(RM) $(FT_NAME)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean
