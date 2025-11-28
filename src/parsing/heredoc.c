/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:33:03 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 15:34:45 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc_file(t_shell *data, t_redir *redir)
{
	int		fd;
	int		expand;
	char	*clean;

	expand = should_expand_delimiter(redir->filename);
	clean = clean_delimiter(data, redir->filename);
	redir->heredoc_path = generate_hd_filename(data);
	fd = open(redir->heredoc_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (read_and_write_heredoc(data, fd, clean, expand) != 0)
	{
		close(fd);
		unlink(redir->heredoc_path);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_heredocs(t_shell *data, t_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_DELIMITER)
				if (process_heredoc_file(data, redir) != 0)
					return (-1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
