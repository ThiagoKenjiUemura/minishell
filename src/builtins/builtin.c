/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:09:35 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/17 20:53:55 by liferrei         ###   ########.fr       */
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
static int	execute_builtin(t_shell *data)
{
	char	*cmd;

	cmd = data->name_cmd->cmd;
/*	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(data->name_cmd->args));

	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(data->envp));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(data->name_cmd->args, data));
*/
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(data, data->name_cmd));
	return (0);
}
int	execute(t_shell *data)
{
	if(!data->name_cmd)
		return (0);
	if (data->name_cmd->is_builtin)
		return(execute_builtin(data));
	return (0);
}
