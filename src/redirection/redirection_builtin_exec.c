/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_builtin_exec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:26:57 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 11:27:25 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_with_redirs(t_cmd *cmd, t_shell *data)
{
	int	sin;
	int	sout;
	int	ret;

	sin = dup(STDIN_FILENO);
	sout = dup(STDOUT_FILENO);
	if (sin < 0 || sout < 0)
		return (1);
	if (apply_redirections(cmd))
		return (dup2(sin, STDIN_FILENO), dup2(sout, STDOUT_FILENO),
			close(sin), close(sout), 1);
	if (cmd->input_fd != STDIN_FILENO)
		dup2(cmd->input_fd, STDIN_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
		dup2(cmd->output_fd, STDOUT_FILENO);
	ret = execute_builtin(data, cmd);
	dup2(sin, STDIN_FILENO);
	dup2(sout, STDOUT_FILENO);
	close(sin);
	close(sout);
	return (ret);
}
