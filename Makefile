# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 14:10:24 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/11/18 16:56:31 by kaisuzuk         ###   ########.fr        #
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
			sig.c \
			sig_utils.c \
			tokenize.c \
			tokenize_make.c \
			tokenize_utils_tokenkinds.c \
			tokenize_utils.c \
			parser.c \
			parser_redirect.c \
			parser_utils.c \
			parser_error.c \
			parser_utils_tokenkinds.c \
			expand.c \
			expand_utils.c \
			expand_quote_removal.c \
			expand_ifs_split.c \
			subst.c \
			subst_get.c \
			dispose_cmd.c \
			dispose_token.c \
			dispose_env.c \
			execute_pipeline.c \
			execute_pipeline_utils.c \
			execute_cmd.c \
			execute_wait.c \
			findcmd.c \
			findcmd_utils.c \
			list.c \
			strvec.c \
			redir.c \
			redir_heredoc.c \
			make_cmd.c \
			make_cmd_utils.c \
			ft_mkstemp.c \
			execute_builtin.c \
			execute_builtin_utils.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			ft_strtoimax.c \
			builtin_export.c \
			builtin_export_utils.c \
			builtin_unset.c \
			builtin_pwd.c \
			builtin_cd.c \
			builtin_cd_utils.c \
			builtin_cd_interpret.c \
			builtin_cd_env.c \
			builtin_cd_canonpath.c \
			variables.c \
			variables_specials.c \
			variables_alloc.c \
			variables_set.c \
			variables_get.c \
			env.c \
			env_get.c \
			env_set.c \
			error.c \
			error_parse.c \
			xmalloc.c


OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FT_NAME) $(OBJS)
	$(MAKE) $(FT_NAME)
	$(CC) -o $(NAME) $(DEBUG) $(FLAG) $(INC) $(OBJS) -lreadline -L$(FT_NAME) -lftprintf

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