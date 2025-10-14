# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 14:10:24 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/10/14 14:05:29 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell
CC		=	cc
FLAG	=	-Wall -Werror -Wextra
INC		=	-Iincludes

SANITIZE	=	-fsanitize=address
DEBUG	=	-g

MAKE	=	make -C
RM		=	rm -rf

FT_NAME	=	libftprintf
FT_URL	=	https://github.com/kaisuzuk2/ft_dprintf.git
INC		+=	-I$(FT_NAME)/includes
INC		+=	-I$(FT_NAME)/libft

SRCS	=	minishell.c \
			bashline.c \
			tokenize.c \
			parser.c \
			expand.c \
			dispose_cmd.c 

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FT_NAME) $(OBJS)
	$(MAKE) $(FT_NAME)
	$(CC) -o $(NAME) $(DEBUG) $(FLAG) $(INC) $(OBJS) -lreadline -L$(FT_NAME) -lftprintf -lbsd

%.o: %.c
	$(CC) -c  $(INC) -g $< -o $@

$(FT_NAME): 
	git clone $(FT_URL) $(FT_NAME)

clean:
	$(RM) $(FT_NAME)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean