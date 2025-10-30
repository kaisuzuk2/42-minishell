/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:12:50 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/10/30 15:26:42 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern char **environ;

# ifndef HEREDOC_PIPESIZE
#  ifdef PIPE_BUF
#   define HEREDOC_PIPESIZE PIPE_BUF
#  else
#   define HEREDOC_PIPESIZE 4096
#  endif
# endif

typedef int t_bool;
#define TRUE 1
#define FALSE 0

# define EX_FATAL_ERROR 2
# define EX_NOEXEC 126
# define EX_NOTFOUND 127
// # define EX_SHERRBASE 256

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/stat.h>

#include "command.h"
#include "builtin.h"
#include "externs.h"
#include "dispose_cmd.h"
#include "variables.h"
#include "error.h"
#include "xmalloc.h"
#include "variables.h"

#include "ft_printf.h"
#include "libft.h"

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'

# define EXECUTION_FAILURE 1
# define EXECUTION_SUCCESS 0

typedef struct s_pipefd
{
	int					pipe_in;
	int					pipe_out;
}						t_pipefd;


#endif