/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:47:28 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 16:47:58 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_signal = 0;

static	void	update_exit_status(t_shell *data, int status)
{
	if (g_last_signal != 0)
	{
		data->last_exit_status = g_last_signal;
		g_last_signal = 0;
	}
	else if (WIFEXITED(status))
		data->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_exit_status = 128 + WTERMSIG(status);
}

void	wait_for_children(t_shell *data, pid_t last_pid)
{
	pid_t	wpid;
	int		status;

	if (last_pid == -1)
	{
		while (waitpid(-1, &status, 0) > 0)
			;
		return ;
	}
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid <= 0)
			break ;
		if (wpid == last_pid)
			update_exit_status(data, status);
	}
}

int	execute(t_shell *data)
{
	int	result;

	result = 0;
	if (!data->name_cmd)
		return (0);
	result = execute_pipeline(data, data->name_cmd);
	if (g_last_signal != 0)
	{
		data->last_exit_status = g_last_signal;
		g_last_signal = 0;
	}
	return (result);
}
