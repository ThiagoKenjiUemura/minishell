/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:47:04 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/27 10:17:26 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_hd_filename(t_shell *data)
{
	int		count;
	char	*num;
	char	*path;

	count = 0;
	num = garbage_itoa(data, count++);
	path = garbage_strjoin(data, "/tmp/minishell_hd_", num);
	return (path);
}

static int	read_and_write_heredoc(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (0);
		//line = expand_heredoc_line(data, line, delimiter);
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

static	int	process_heredoc_file(t_shell *data, t_redir *redir)
{
	int		fd;

	redir->heredoc_path = generate_hd_filename(data);
	if (!redir->heredoc_path)
		return (-1);
	fd = open(redir->heredoc_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (read_and_write_heredoc(redir->filename, fd) != 0)
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
			{
				if (process_heredoc_file(data, redir) != 0)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
