/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:59:08 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/04 18:40:54 by tkenji-u         ###   ########.fr       */
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

static pid_t	exec_command(t_shell *data, t_cmd *cmd,
			int *fd_pipe, int is_pipe)
{
	if (cmd->is_builtin && !cmd->next && !is_pipe)
		return (handle_single_builtin(data, cmd));
	return (spawn_child(data, cmd, fd_pipe));
}

static pid_t	handle_pipe_step(t_shell *data, t_cmd *cmd,
			int *fd_in, int is_pipe)
{
	int		fd_pipe[2];
	pid_t	pid;

	setup_cmd_fds(cmd, fd_in, fd_pipe);
	pid = exec_command(data, cmd, fd_pipe, is_pipe);
	cleanup_fds(cmd, fd_in, fd_pipe);
	return (pid);
}

int	execute_pipeline(t_shell *data, t_cmd *cmd_list)
{
	int		fd_in;
	pid_t	last_pid;
	int		is_pipe;

	fd_in = STDIN_FILENO;
	last_pid = -1;
	is_pipe = 0;
	if (cmd_list && cmd_list->next)
		is_pipe = 1;
	while (cmd_list)
	{
		last_pid = handle_pipe_step(data, cmd_list, &fd_in, is_pipe);
		cmd_list = cmd_list->next;
	}
	wait_for_children(data, last_pid);
	return (data->last_exit_status);
}
