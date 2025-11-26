/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:37:56 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/26 02:20:17 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_redir *r)
{
	int	fd;

	if (r->type == REDIR_DELIMITER && r->heredoc_path)
		fd = open(r->heredoc_path, O_RDONLY);
	else
		fd = open(r->filename_or_delimiter, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	open_outfile(t_redir *r)
{
	int	fd;
	int	flags;

	if (r->type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(r->filename_or_delimiter, flags, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN || r->type == REDIR_DELIMITER)
		{
			fd = open_infile(r);
			if (fd < 0)
				return (-1);
			dup2(fd, STDIN_FILENO);
		}
		else if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
		{
			fd = open_outfile(r);
			if (fd < 0)
				return (-1);
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		r = r->next;
	}
	return (0);
}
