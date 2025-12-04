/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:53:45 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/04 14:06:50 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_handle_redirs(t_shell *data, t_cmd *cmd)
{
	if (apply_redirections(cmd))
	{
		free_shell(data);
		exit(1);
	}
	handle_fds(cmd);
}

static void	child_validate_args(t_shell *data, t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
	{
		free_shell(data);
		exit(0);
	}
	if (!cmd->args[0][0])
	{
		print_exec_error("", "command not found");
		free_shell(data);
		exit(127);
	}
}

static void	child_exec_final(t_shell *data, t_cmd *cmd, char *path)
{
	if (!path)
	{
		print_exec_error(cmd->args[0], "command not found");
		free_shell(data);
		exit(127);
	}
	check_dir_and_perm(path, cmd->args[0], data);
	execve(path, cmd->args, data->envp);
	print_exec_error(cmd->args[0], "execve failed");
	free(path);
	free_shell(data);
	exit(1);
}

void	execute_child_process(t_shell *data, t_cmd *cmd)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_handle_redirs(data, cmd);
	child_validate_args(data, cmd);
	path = get_cmd_path(data, cmd->args[0]);
	child_exec_final(data, cmd, path);
}
