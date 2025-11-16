/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:12:50 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/16 15:21:31 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "general.h"
# include "builtin.h"
# include "command.h"
# include "dispose_cmd.h"
# include "error.h"
# include "externs.h"
# include "ft_printf.h"
# include "libft.h"
# include "sig.h"
# include "subst.h"
# include "variables.h"
# include "xmalloc.h"

extern char	**environ;

# define STDFD_SIZE 3

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define DOLLAR_CHAR '$'

# define EXECUTION_FAILURE 1
# define EXECUTION_SUCCESS 0
# define EXECUTION_ERR -1
# define EXECUTION_MEMERR -2

# define EX_SYNTAX_ERROR 2
# define EX_FATAL_ERROR 2
# define EX_NOEXEC 126
# define EX_NOTFOUND 127

#endif