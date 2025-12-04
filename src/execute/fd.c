/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:06:14 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/04 14:10:51 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_cmd_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2])
{
	if (cmd->next)
		pipe(fd_pipe);
	cmd->input_fd = *fd_in;
	if (cmd->next && !has_output_redirection(cmd))
		cmd->output_fd = fd_pipe[1];
	else
		cmd->output_fd = STDOUT_FILENO;
}

void	cleanup_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2])
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (cmd->next)
	{
		close(fd_pipe[1]);
		*fd_in = fd_pipe[0];
	}
}
