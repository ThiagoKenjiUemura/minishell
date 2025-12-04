/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:47:10 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/04 13:58:28 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fds(t_cmd *cmd)
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

void	print_exec_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

void	check_dir_and_perm(char *path, char *cmd_name, t_shell *data)
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

char	*get_cmd_path(t_shell *data, char *cmd_name)
{
	char	*path;

	if (ft_strchr(cmd_name, '/'))
		path = ft_strdup(cmd_name);
	else
		path = find_in_path(cmd_name, data->envp);
	return (path);
}
