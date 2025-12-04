/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:47:04 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 11:42:20 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_hd_filename(t_shell *data)
{
	static int	count = 0;
	char		*num;
	char		*path;

	num = garbage_itoa(data, count++);
	path = garbage_strjoin(data, "/tmp/minishell_hd_", num);
	return (path);
}

int	should_expand_delimiter(char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if ((delim[0] == '\'' && delim[len - 1] == '\'')
		|| (delim[0] == '"' && delim[len - 1] == '"'))
		return (0);
	return (1);
}

char	*clean_delimiter(t_shell *data, char *delim)
{
	int	len;

	len = ft_strlen(delim);
	if ((delim[0] == '\'' && delim[len - 1] == '\'')
		|| (delim[0] == '"' && delim[len - 1] == '"'))
		return (garbage_substr(data, delim, 1, len - 2));
	return (garbage_strdup(data, delim));
}

void	write_line(t_shell *data, int fd, char *line, int expand)
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

int	finish_heredoc(int stdin_backup, int return_value)
{
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (return_value);
}
