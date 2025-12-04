/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_builtin_exec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:43:20 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 18:30:57 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_std_fds(int *sin, int *sout)
{
	*sin = dup(STDIN_FILENO);
	*sout = dup(STDOUT_FILENO);
	if (*sin < 0 || *sout < 0)
		return (1);
	return (0);
}

static void	restore_std_fds(int sin, int sout)
{
	dup2(sin, STDIN_FILENO);
	dup2(sout, STDOUT_FILENO);
	close(sin);
	close(sout);
}

int	setup_builtin_redirs(t_cmd *cmd)
{
	if (apply_redirections(cmd))
	{
		if (cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		if (cmd->output_fd != STDOUT_FILENO)
			close(cmd->output_fd);
		return (1);
	}
	if (cmd->input_fd != STDIN_FILENO)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
	return (0);
}

int	execute_builtin_with_redirs(t_cmd *cmd, t_shell *data, int in_child)
{
	int	sin;
	int	sout;
	int	ret;

	if (save_std_fds(&sin, &sout))
		return (1);
	if (setup_builtin_redirs(cmd))
	{
		restore_std_fds(sin, sout);
		return (1);
	}
	if (in_child && ft_strcmp(cmd->cmd, "exit") == 0)
	{
		close(sin);
		close(sout);
		ft_exit_pipe(data, cmd);
	}
	ret = execute_builtin(data, cmd, in_child);
	restore_std_fds(sin, sout);
	return (ret);
}
