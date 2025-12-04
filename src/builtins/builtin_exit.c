/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:30:51 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 10:32:14 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
	{
		shell->running = 0;
		return (shell->last_exit_status);
	}
	if (cmd->args[1][0] == '\0' || !ft_str_is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->running = 0;
		shell->last_exit_status = 2;
		return (2);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	shell->last_exit_status = ft_atoi(cmd->args[1]);
	shell->running = 0;
	return (shell->last_exit_status);
}

int	ft_exit_pipe(t_shell *data, t_cmd *cmd)
{
	int	code;

	code = 0;
	if (cmd->args && cmd->args[1])
	{
		if (!ft_str_is_numeric(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			code = 2;
		}
		else if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			code = 1;
		}
		else
			code = ft_atoi(cmd->args[1]) % 256;
	}
	free_shell(data);
	exit(code);
}

void	free_redirs(t_redir *r)
{
	t_redir	*tmp;

	while (r)
	{
		tmp = r;
		r = r->next;
		if (tmp->filename)
			free(tmp->filename);
		free(tmp);
	}
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
