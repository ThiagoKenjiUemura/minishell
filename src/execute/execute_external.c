/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* execute_external.c                                 :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/27 10:36:24 by liferrei          #+#    #+#             */
/* Updated: 2025/12/03 13:40:06 by liferrei         ###   ########.fr       */
/* */
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

static void	print_exec_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

static void	check_dir_and_perm(char *path, char *cmd_name, t_shell *data)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		print_exec_error(cmd_name, "No such file or directory");
		free(path);
		free_shell(data);
		exit(127);
	}
	if (S_ISDIR(sb.st_mode))
	{
		print_exec_error(cmd_name, "Is a directory");
		free(path);
		free_shell(data);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		print_exec_error(cmd_name, "Permission denied");
		free(path);
		free_shell(data);
		exit(126);
	}
}

static char	*get_cmd_path(t_shell *data, char *cmd_name)
{
	char	*path;

	if (ft_strchr(cmd_name, '/'))
		path = ft_strdup(cmd_name);
	else
		path = find_in_path(cmd_name, data->envp);
	return (path);
}

void	execute_child_process(t_shell *data, t_cmd *cmd)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (apply_redirections(cmd))
	{
		// [FIX] Limpar memória antes de sair em caso de erro no redirecionamento
		free_shell(data);
		exit(1);
	}
	handle_fds(cmd);
	if (!cmd->args[0])
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
	path = get_cmd_path(data, cmd->args[0]);
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
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}