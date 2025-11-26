/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:58:34 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/26 06:50:04 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// encontra o executável no PATH
char *find_in_path(const char *cmd, char **envp)
{
    char *path_env = env_get(envp, "PATH");
    if (!path_env)
        return NULL;

    char **paths = ft_split(path_env, ':');
    for (int i = 0; paths[i]; i++)
    {
        char *full = ft_strjoin3(paths[i], "/", cmd);
        if (!access(full, X_OK))
        {
            // libera o restante
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return full;
        }
        free(full);
    }
    for (int j = 0; paths[j]; j++)
        free(paths[j]);
    free(paths);
    return NULL;
}

// aplica redirecionamentos (<, >, >>)
int apply_redirections(t_cmd *cmd)
{
    t_redir *r = cmd->redirs;
    int fd;

    while (r)
    {
        if (r->type == 0) // <
        {
            fd = open(r->filename, O_RDONLY);
            if (fd < 0)
            {
                perror(r->filename);
                return 1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (r->type == 1) // >
        {
            fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(r->filename);
                return 1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (r->type == 2) // >>
        {
            fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror(r->filename);
                return 1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        r = r->next;
    }
    return 0;
}

// executa um comando externo (ou via PATH)
int execute_external(t_shell *data, t_cmd *cmd)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0) // filho
    {
        if (apply_redirections(cmd))
            exit(1);

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

        if (cmd->path)
            execve(cmd->path, cmd->args, data->envp);
        else
        {
            char *exec_path = find_in_path(cmd->args[0], data->envp);
            if (exec_path)
            {
                execve(exec_path, cmd->args, data->envp);
                free(exec_path);
            }
        }

        perror(cmd->args[0]);
        exit(127);
    }

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

// executa pipeline de comandos
int execute_pipeline(t_shell *data, t_cmd *cmd_list)
{
    t_cmd *cmd = cmd_list;
    int status = 0;
    int fd_in = STDIN_FILENO;
    int fd_pipe[2];

    while (cmd)
    {
        if (cmd->next)
            pipe(fd_pipe);

        cmd->input_fd = fd_in;
        cmd->output_fd = cmd->next ? fd_pipe[1] : STDOUT_FILENO;

        if (cmd->is_builtin)
        {
            status = execute_builtin(data);
            data->last_exit_status = status;
        }
        else
        {
            status = execute_external(data, cmd);
            data->last_exit_status = status;
        }

        if (fd_in != STDIN_FILENO)
            close(fd_in);
        if (cmd->next)
        {
            close(fd_pipe[1]);
            fd_in = fd_pipe[0];
        }

        cmd = cmd->next;
    }
    return status;
}

// função principal de execução
int execute(t_shell *data)
{
    if (!data->name_cmd)
        return 0;

    return execute_pipeline(data, data->name_cmd);
}
