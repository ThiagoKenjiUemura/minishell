/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:36:24 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/03 13:40:06 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_fds(t_cmd *cmd)
{
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
}

static void	handle_execve(t_shell *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		execve(cmd->args[0], cmd->args, data->envp);
		return;
	}
	char	*exec_path = find_in_path(cmd->args[0], data->envp);
	if (exec_path)
	{
		execve(exec_path, cmd->args, data->envp);
		free(exec_path);
		return;
	}
}
void	execute_child_process(t_shell *data, t_cmd *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (apply_redirections(cmd))
		exit(1);
	handle_fds(cmd);
	handle_execve(data, cmd);
	if (ft_strchr(cmd->args[0], '/'))
		perror(cmd->args[0]);
	else
		ft_printf("%s: command not found\n", cmd->args[0]);
	free_shell(data);
	exit(127);
}

/* Executes external commands. */
int	execute_external(t_shell *data, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		init_child_signals();
		execute_child_process(data, cmd);
		exit(127);       //add depois
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

