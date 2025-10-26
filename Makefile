# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 14:10:24 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/10/26 14:41:32 by kaisuzuk         ###   ########.fr        #
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
			tokenize_utils_tokenkinds.c \
			tokenize_utils.c \
			parser.c \
			parser_redirect.c \
			parser_utils.c \
			parser_error.c \
			parser_is_tokenkind.c \
			expand.c \
			expand_utils.c \
			subst.c \
			dispose_cmd.c \
			execute_pipeline.c \
			execute_pipeline_utils.c \
			findcmd.c \
			findcmd_utils.c \
			list.c \
			strvec.c \
			redir.c \
			make_cmd.c \
			ft_mkstemp.c \
			builtin.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_export.c \
			builtin_unset.c \
			builtin_pwd.c \
			builtin_cd.c \
			variables.c \
			error.c \
			xmalloc.c


OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FT_NAME) $(OBJS)
	$(MAKE) $(FT_NAME)
	$(CC) -o $(NAME) $(DEBUG) $(FLAG) $(SANITIZE) $(INC) $(OBJS) -lreadline -L$(FT_NAME) -lftprintf

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