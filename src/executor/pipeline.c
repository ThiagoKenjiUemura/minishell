/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:32:10 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/26 02:24:59 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe(t_cmd *cmd, int fds[2])
{
	if (cmd->next)
		pipe(fds);
	else
	{
		fds[0] = STDIN_FILENO;
		fds[1] = STDOUT_FILENO;
	}
}

static void	run_process(t_cmd *cmd, t_shell *data, int prev_fd, int fds[2])
{
	int	out_fd;

	out_fd = cmd->next ? fds[1] : STDOUT_FILENO;
	run_child(cmd, data, prev_fd, out_fd);
}

static void	close_and_update_prev(int *prev_fd, int fds[2], t_cmd *cmd)
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fds[1]);
		*prev_fd = fds[0];
	}
}

int	execute_pipeline(t_shell *data)
{
	t_cmd	*cmd;
	int		fds[2];
	int		prev_fd;
	pid_t	pids[256];
	int		i;

	cmd = data->name_cmd;
	prev_fd = STDIN_FILENO;
	i = 0;
	while (cmd)
	{
		handle_pipe(cmd, fds);
		pids[i] = fork();
		if (pids[i] == 0)
			run_process(cmd, data, prev_fd, fds);
		close_and_update_prev(&prev_fd, fds, cmd);
		cmd = cmd->next;
		i++;
	}
	return (wait_children(pids, i, data));
}
