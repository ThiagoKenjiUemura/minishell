/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* redirection_builtin_exec.c                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/27 11:26:57 by liferrei          #+#    #+#             */
/* Updated: 2025/11/28 17:45:36 by liferrei         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_with_redirs(t_cmd *cmd, t_shell *data, int in_child)
{
	int	sin;
	int	sout;
	int	ret;

	sin = dup(STDIN_FILENO);
	sout = dup(STDOUT_FILENO);
	if (sin < 0 || sout < 0)
		return (1);
	if (apply_redirections(cmd))
	{
		dup2(sin, STDIN_FILENO);
		dup2(sout, STDOUT_FILENO);
		close(sin);
		close(sout);
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
	if (in_child && ft_strcmp(cmd->cmd, "exit") == 0)
	{
		// [FIX] Fecha backups de STDIN/STDOUT antes de sair para evitar leaks
		close(sin);
		close(sout);
		ft_exit_pipe(data, cmd);
	}
	ret = execute_builtin(data, cmd, in_child);
	dup2(sin, STDIN_FILENO);
	dup2(sout, STDOUT_FILENO);
	close(sin);
	close(sout);
	return (ret);
}