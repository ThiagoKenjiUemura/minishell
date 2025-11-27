/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:47:04 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/27 16:08:24 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_hd_filename(t_shell *data)
{
	static int	count = 0;
	char		*num;
	char		*path;

	num = garbage_itoa(data, count++);
	path = garbage_strjoin(data, "/tmp/minishell_hd_", num);
	return (path);
}

static int	should_expand_delimiter(char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if ((delim[0] == '\'' && delim[len - 1] == '\'')
		|| (delim[0] == '"' && delim[len - 1] == '"'))
		return (0);
	return (1);
}

static char	*clean_delimiter(t_shell *data, char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if ((delim[0] == '\'' && delim[len - 1] == '\'')
		|| (delim[0] == '"' && delim[len - 1] == '"'))
		return (garbage_substr(data, delim, 1, len - 2));
	return (garbage_strdup(data, delim));
}

static void	write_line(t_shell *data, int fd, char *line, int expand)
{
	char	*expanded;

	if (expand)
	{
		expanded = sub_var_in_str(data, line);
		if (expanded)
			write(fd, expanded, ft_strlen(expanded));
		else
			write(fd, line, ft_strlen(line));
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	read_and_write_heredoc(t_shell *data, int fd,
	char *delimiter, int expand)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_line(data, fd, line, expand);
		free(line);
	}
	return (0);
}

static int	process_heredoc_file(t_shell *data, t_redir *redir)
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
