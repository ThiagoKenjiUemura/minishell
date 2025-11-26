/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:58:34 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/26 06:02:39 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(t_shell *data)
{
    int     status;
    t_cmd   *cmd;

	status = 0;
    cmd = data->name_cmd;
    if (!cmd || !cmd->args || !cmd->args[0])
        return (0);
    if (cmd->is_builtin)
    {
        status = execute_builtin(data);
        data->last_exit_status = status;
        return (status);
    }
    status = execute_external(data, cmd);
    data->last_exit_status = status;
    return (status);
}

int	execute_external(t_shell *data, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        if (cmd->path)
            execve(cmd->path, cmd->args, data->envp);
        else
            execve(cmd->args[0], cmd->args, data->envp);
		perror(cmd->args[0]);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}