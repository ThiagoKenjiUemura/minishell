/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:09:35 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/17 16:30:06 by liferrei         ###   ########.fr       */
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

int	execute(t_shell *data)
{
	if(!data->name_cmd)
		return (0);
	if (data->name_cmd->is_builtin)
		return(execute_builtin(data));
	return (0);
}

int	execute_builtin(t_shell *data)
{
	char	*cmd;

	cmd = data->name_cmd->cmd;
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(data->name_cmd->args));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(data->envp));
	if (ft_strcmp(cmd, "exit") == 0)
		return (ft_cd(data->name_cmd->args, data));
	return (0);
}
// Excluir depois que integrar ao parse do thiago 
void fake_parser(t_shell *data)
{
    t_cmd *cmd;
    char **tokens;

    if (!data->input || !*data->input)
    {
        data->name_cmd = NULL;
        return ;
    }

    tokens = ft_split(data->input, ' ');
    if (!tokens)
    {
        data->name_cmd = NULL;
        return ;
    }

    cmd = garbage_calloc(data, sizeof(t_cmd));
    if (!cmd)
    {
        data->name_cmd = NULL;
        return ;
    }

    cmd->cmd = tokens[0];
    cmd->args = tokens;
    cmd->is_builtin = is_builtin(cmd->cmd);
    cmd->input_fd = STDIN_FILENO;
    cmd->output_fd = STDOUT_FILENO;
    cmd->next = NULL;

    data->name_cmd = cmd;
}