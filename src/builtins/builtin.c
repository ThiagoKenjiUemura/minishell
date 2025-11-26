/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:09:35 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/26 02:11:21 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	run_builtin(t_shell *data, t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (0);
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd->args));
	if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env(data, cmd->args));
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(data, cmd->args));
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(data, cmd->args));
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(data, cmd));
	return (0);
}

