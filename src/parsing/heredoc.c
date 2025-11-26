/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:47:04 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/25 20:38:41 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_and_write_heredoc(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	process_heredoc_file(t_shell *data, t_redir *redir)
{
	int		fd;
	char	*delimiter;

	(void)data;
	delimiter = redir->filename_or_delimiter;
	fd = open("/tmp/hd_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (read_and_write_heredoc(delimiter, fd) != 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	redir->type = REDIR_IN;
	redir->filename_or_delimiter = "/tmp/hd_temp";
	return (0);
}

int	handle_heredocs(t_shell *data, t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		current_redir = current_cmd ->redirs;
		while (current_redir)
		{
			if (current_redir->type == REDIR_DELIMITER)
			{
				if (process_heredoc_file(data, current_redir) != 0)
					return (-1);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}
