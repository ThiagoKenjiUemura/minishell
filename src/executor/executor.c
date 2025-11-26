/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:31:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/26 02:30:11 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_shell *data)
{
	t_cmd	*cmd;

	if (!data || !data->name_cmd)
		return (0);
	cmd = data->name_cmd;
	if (cmd->next)
		return (execute_pipeline(data));
	return (exec_single_cmd(cmd, data));
}

void run_child(t_cmd *cmd, t_shell *data, int prev_in, int next_out)
{
	if (prev_in != STDIN_FILENO)
	{
		dup2(prev_in, STDIN_FILENO);
		close(prev_in);
	}
	if (next_out != STDOUT_FILENO)
	{
		dup2(next_out, STDOUT_FILENO);
		close(next_out);
	}
	if (apply_redirections(cmd) == -1)
		exit(1);
	if (cmd->is_builtin)
		exit(run_builtin(data, cmd));
	execve(cmd->cmd, cmd->args, data->envp);
	perror("minishell");
	exit(127);
}

int wait_children(pid_t *pids, int count, t_shell *data)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	data->last_exit_status = WEXITSTATUS(status);
	return data->last_exit_status;
}
