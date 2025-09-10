/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:39:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/09/10 11:36:11 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash memo
/* Execute the command passed in COMMAND.  COMMAND is exactly what
   read_command () places into GLOBAL_COMMAND.  See "command.h" for the
   details of the command structure.

   EXECUTION_SUCCESS or EXECUTION_FAILURE are the only possible
   return values.  Executing a command with nothing in it returns
   EXECUTION_SUCCESS. */

/*

TODO:
1) argument change

*/

/*

1) If a command name matches a special built-in utility name, that special built-in utility is invoked.
2) If a command name matches a utility name listed in the following table, the result is unspecified. (list: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
3) If a command name matches a function name known to this shell, that function is invoked as described in the Function Definition Command section. If the implementation provides a standard utility in the form of a function, it should not be recognized at this point. It should be invoked in combination with the path search in step 1e.
4) If the command name matches the name of the type or ulimit utility, or a utility listed in the following table, that utility shall be invoked.
5) Otherwise, the command shall be searched for using the PATH environment variable as described in XBD Environment Variables :
*/

int execute_command(char *readline, char **envp)
{
	char *line[] = {readline, NULL};
	int status;
	
	const pid_t pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		execve(line[0], line, envp);
		return (0);
	}
	else
	{
		wait(&status);
		return (0);
	}
}
