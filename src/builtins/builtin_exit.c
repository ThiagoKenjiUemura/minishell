/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:30:07 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/17 20:45:06 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(t_shell *shell, t_cmd *cmd)
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
            ft_printf("exit: %s: numeric argument required\n",
                cmd->args[1]);
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

