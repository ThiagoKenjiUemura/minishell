/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:09:35 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/26 17:33:19 by liferrei         ###   ########.fr       */
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

int execute_builtin(t_shell *data, t_cmd *cmd)
{
    char *name;

    if (!cmd || !cmd->cmd)
        return (0);
    name = cmd->cmd;
    if (ft_strcmp(name, "cd") == 0)
        return ft_cd(cmd->args);
    if (ft_strcmp(name, "env") == 0)
        return ft_env(data, cmd->args);
    if (ft_strcmp(name, "echo") == 0)
        return ft_echo(cmd->args);
    if (ft_strcmp(name, "pwd") == 0)
        return ft_pwd();
    if (ft_strcmp(name, "export") == 0)
        return ft_export(data, cmd->args);
    if (ft_strcmp(name, "unset") == 0)
        return ft_unset(data, cmd->args);
    if (ft_strcmp(name, "exit") == 0)
        return ft_exit(data, cmd);

    return 0;
}
