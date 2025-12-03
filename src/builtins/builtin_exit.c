/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:30:07 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/03 14:52:36 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, t_cmd *cmd)
{

	ft_printf("exit\n");
	if (!cmd->args[1])
	{
		shell->running = 0;
		return (shell->last_exit_status);
	}
	if (cmd->args[1][0] == '\0' || !ft_str_is_numeric(cmd->args[1]))
	{
		if (cmd->args[1][0] == '\0')
			ft_printf("exit: : numeric argument required\n");
		else
			ft_printf("exit: %s: numeric argument required\n", cmd->args[1]);
		shell->running = 0;
		shell->last_exit_status = 2;
		return (2);
	}
	if (cmd->args[2])
	{
		ft_printf("exit: too many arguments\n");
		shell->last_exit_status = 1;
		return (1);
	}
	shell->last_exit_status = ft_atoi(cmd->args[1]);
	shell->running = 0;
	return (shell->last_exit_status);
}
int ft_exit_pipe(t_shell *data, t_cmd *cmd)
{
    int code;

    (void)data;
	code = 0;
    if (cmd->args && cmd->args[1])
        code = ft_atoi(cmd->args[1]) % 256;
    else
        code = 0;
    if (cmd->cmd)
        free(cmd->cmd);
    if (cmd->args)
        free_args(cmd->args);
    if (cmd->redirs)
        free_redirs(cmd->redirs);
    exit(code);
}
void free_redirs(t_redir *r)
{
    t_redir *tmp;

    while (r)
    {
        tmp = r;
        r = r->next;
        if (tmp->filename)
            free(tmp->filename);
        free(tmp);
    }
}
void free_args(char **args)
{
    int i;

    if (!args)
        return;

    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}