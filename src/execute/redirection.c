/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:21:54 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 10:50:31 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check for outbound traffic redirection. */
int	has_output_redirection(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_OUT
			|| r->type == REDIR_APPEND)
			return (1);
		r = r->next;
	}
	return (0);
}

/*Executes builtins with redirects applied. */
int	execute_builtin_with_redirs(t_cmd *cmd, t_shell *data)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		return (1);
	if (apply_redirections(cmd))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
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
	ret = execute_builtin(data, cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			fd = open(r->filename, O_RDONLY);
			if (fd < 0)
				return (perror(r->filename), -1);
			if (cmd->input_fd != STDIN_FILENO)
				close(cmd->input_fd);
			cmd->input_fd = fd;
		}
		else if (r->type == REDIR_OUT)
		{
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(r->filename), -1);
			if (cmd->output_fd != STDOUT_FILENO)
				close(cmd->output_fd);
			cmd->output_fd = fd;
		}
		else if (r->type == REDIR_APPEND)
		{
			fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(r->filename), -1);
			if (cmd->output_fd != STDOUT_FILENO)
				close(cmd->output_fd);
			cmd->output_fd = fd;
		}
		else if (r->type == REDIR_DELIMITER)
		{
			if (cmd->input_fd != STDIN_FILENO)
				close(cmd->input_fd);
			cmd->input_fd = open(r->heredoc_path, O_RDONLY);
			if (cmd->input_fd < 0)
				return (perror("heredoc"), -1);
		}
		r = r->next;
	}
	return (0);
}
