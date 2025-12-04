/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:59:08 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/04 18:27:22 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_builtin(t_shell *data, t_cmd *cmd)
{
	data->last_exit_status = execute_builtin_with_redirs(cmd, data, 0);
	return (-1);
}

static pid_t	spawn_child(t_shell *data, t_cmd *cmd, int *fd_pipe)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (cmd->next)
			close(fd_pipe[0]);
		if (cmd->is_builtin)
		{
			ret = execute_builtin_with_redirs(cmd, data, 1);
			free_shell(data);
			exit(ret);
		}
		execute_child_process(data, cmd);
	}
	return (pid);
}

static pid_t	exec_command(t_shell *data, t_cmd *cmd, int *fd_pipe, int next, int is_pipe)
{
	if (cmd->is_builtin && !next && !is_pipe)
		return (handle_single_builtin(data, cmd));
	return (spawn_child(data, cmd, fd_pipe));
}

int	execute_pipeline(t_shell *data, t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		fd_in;
	int		fd_pipe[2];
	pid_t	last_pid;
	int		has_next;
	int		is_pipe;

	cmd = cmd_list;
	fd_in = STDIN_FILENO;
	last_pid = -1;
	is_pipe = 0;
	if (cmd_list && cmd_list->next)
		is_pipe = 1;

	while (cmd)
	{
		setup_cmd_fds(cmd, &fd_in, fd_pipe);
		has_next = (cmd->next != NULL);
		// ALTERAÇÃO 3: Passar 'is_pipe' para a função
		last_pid = exec_command(data, cmd, fd_pipe, has_next, is_pipe);
		cleanup_fds(cmd, &fd_in, fd_pipe);
		cmd = cmd->next;
	}
	wait_for_children(data, last_pid);
	return (data->last_exit_status);
}
