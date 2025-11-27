/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:21:27 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 11:21:50 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_infile(t_cmd *cmd, t_redir *r)
{
	int	fd;

	fd = open(r->filename, O_RDONLY);
	if (fd < 0)
		return (perror(r->filename), -1);
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = fd;
	return (0);
}

int	apply_outfile(t_cmd *cmd, t_redir *r)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(r->filename), -1);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = fd;
	return (0);
}

int	apply_append(t_cmd *cmd, t_redir *r)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(r->filename), -1);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = fd;
	return (0);
}

int	apply_delimiter(t_cmd *cmd, t_redir *r)
{
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = open(r->heredoc_path, O_RDONLY);
	if (cmd->input_fd < 0)
		return (perror("heredoc"), -1);
	return (0);
}
