/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 12:36:23 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/11/18 16:10:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

# ifndef HEREDOC_PIPESIZE
#  ifdef PIPE_BUF
#   define HEREDOC_PIPESIZE PIPE_BUF
#  else
#   define HEREDOC_PIPESIZE 4096
#  endif
# endif

# define PATH_KEY "PATH="
# define PWD_KEY "PWD="
# define PWD "PWD"
# define OLDPWD_KEY "OLDPWD"
# define OLDPWD "OLDPWD"
# define CDPATH "CDPATH"
#endif