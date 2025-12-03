/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:58:34 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/03 09:44:18 by liferrei         ###   ########.fr       */
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
static int execute_pipeline(t_shell *data, t_cmd *cmd_list)
{
    t_cmd *cmd = cmd_list;
    int status = 0;
    int fd_in = STDIN_FILENO;
    int fd_pipe[2];
    pid_t pid;

    while (cmd)
    {
        setup_cmd_fds(cmd, &fd_in, fd_pipe);

        int has_next = (cmd->next != NULL);

        if (cmd->is_builtin && !has_next)
        {
            status = execute_builtin_with_redirs(cmd, data, 0);
            data->last_exit_status = status;
        }
        else
        {
            // PIPE / BUILTIN EM PIPE → EXECUTA NO FILHO
            pid = fork();
            if (pid < 0)
            {
                perror("fork");
            }
            else if (pid == 0)
            {
                // FILHO
                if (cmd->is_builtin)
                {
                    int ret = execute_builtin_with_redirs(cmd, data, 1);
                    exit(ret);
                }
                else
                {
                    execute_child_process(data, cmd);
                }
            }
            else
            {
                // PAI
                waitpid(pid, &status, 0);
				if (g_last_signal != 0)
				{
					data->last_exit_status = g_last_signal;
					g_last_signal = 0;
				}
				else if (WIFEXITED(status))
					data->last_exit_status = WEXITSTATUS(status);
            }
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
	if (g_last_signal != 0)
	{
	data->last_exit_status = g_last_signal;
	g_last_signal = 0;
	}
	return (result);
}