/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:58:34 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/28 16:12:54 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prepares the file descriptors for the current command. */
static void	setup_cmd_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2])
{
	if (cmd->next)
		pipe(fd_pipe);
	cmd->input_fd = *fd_in;
	if (cmd->next && !has_output_redirection(cmd))
		cmd->output_fd = fd_pipe[1];
	else
		cmd->output_fd = STDOUT_FILENO;
}

/* Close unnecessary file descriptors. */
static void	cleanup_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2])
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (cmd->next)
	{
		close(fd_pipe[1]);
		*fd_in = fd_pipe[0];
	}
}

static int	execute_pipeline(t_shell *data, t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		status;
	int		fd_in;
	int		fd_pipe[2];
	int		in_pipeline;
	

	cmd = cmd_list;
	fd_in = STDIN_FILENO;
	status = 0;
    while (cmd)
    {
        setup_cmd_fds(cmd, &fd_in, fd_pipe);

        if (cmd->is_builtin)
        {
            in_pipeline = (cmd->next != NULL || fd_in != STDIN_FILENO);
            if (in_pipeline)
            {
                pid_t pid = fork();
                if (pid < 0)
                    perror("fork");
                else if (pid == 0)
                {
                    int ret = execute_builtin_with_redirs(cmd, data, 1);
                    exit(ret);
                }
                else
                {
                    waitpid(pid, &status, 0);
                    data->last_exit_status = WEXITSTATUS(status);
				}
			}
			else
			{
				data->last_exit_status = execute_builtin_with_redirs(cmd, data, 0);
			}
		}
		else
		{
			data->last_exit_status = execute_external(data, cmd);
		}
		cleanup_fds(cmd, &fd_in, fd_pipe);
		cmd = cmd->next;
	}
	return data->last_exit_status;
}

/*Main execution function */
int	execute(t_shell *data)
{
	int	result;

	result = 0;
	if (!data->name_cmd)
		return (0);
	result = execute_pipeline(data, data->name_cmd);
	return (result);
}
