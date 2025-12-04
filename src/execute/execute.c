/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* execute.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/26 05:58:34 by liferrei          #+#    #+#             */
/* Updated: 2025/12/03 09:44:18 by liferrei         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

/* Prepares the file descriptors for the current command. */
static void	setup_cmd_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2])
{
	if (cmd->next)
		pipe(fd_pipe);
	cmd->input_fd = *fd_in;
	if (cmd->next && !has_output_redirection(cmd))
		cmd->output_fd = fd_pipe[1];
	else
		cmd->output_fd = STDOUT_FILENO;
}

/* Close unnecessary file descriptors. */
static void	cleanup_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2])
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (cmd->next)
	{
		close(fd_pipe[1]);
		*fd_in = fd_pipe[0];
	}
}

static void	wait_for_children(t_shell *data, pid_t last_pid)
{
	pid_t	wpid;
	int		status;

	if (last_pid == -1)
	{
		// Se o ultimo comando rodou no pai, apenas esperamos os filhos restantes
		// para evitar zumbis, mas nao atualizamos o last_exit_status.
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
	}
}

static int	execute_pipeline(t_shell *data, t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		fd_in;
	int		fd_pipe[2];
	pid_t	pid;
	pid_t	last_pid;
	int		has_next;

	cmd = cmd_list;
	fd_in = STDIN_FILENO;
	last_pid = -1;
	while (cmd)
	{
		setup_cmd_fds(cmd, &fd_in, fd_pipe);
		has_next = (cmd->next != NULL);
		if (cmd->is_builtin && !has_next)
		{
			data->last_exit_status = execute_builtin_with_redirs(cmd, data, 0);
			last_pid = -1; // [FIX] Ultimo cmd foi no pai, nao esperar PID dele para status
		}
		else
		{
			pid = fork();
			if (pid < 0)
				perror("fork");
			else if (pid == 0)
			{
				if (cmd->next)
					close(fd_pipe[0]);
				if (cmd->is_builtin)
				{
					int ret = execute_builtin_with_redirs(cmd, data, 1);
					free_shell(data);
					exit(ret);
				}
				else
					execute_child_process(data, cmd);
			}
			else
				last_pid = pid;
		}
		cleanup_fds(cmd, &fd_in, fd_pipe);
		cmd = cmd->next;
	}
	wait_for_children(data, last_pid);
	return (data->last_exit_status);
}

/*Main execution function */
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