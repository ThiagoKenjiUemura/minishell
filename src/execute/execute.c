/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:58:34 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 09:01:34 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

/* Concatena três strings */
char *ft_strjoin3(char *s1, char *s2, char *s3)
{
    int len = 0, i = 0;
    char *res;
    char *s;

    s = s1;
    while (s && *s++) len++;
    s = s2;
    while (s && *s++) len++;
    s = s3;
    while (s && *s++) len++;

    res = malloc(len + 1);
    if (!res) return NULL;

    s = s1;
    while (s && *s) res[i++] = *s++;
    s = s2;
    while (s && *s) res[i++] = *s++;
    s = s3;
    while (s && *s) res[i++] = *s++;

    res[i] = '\0';
    return res;
}

/* Executa builtins com redirecionamentos aplicados */
static int execute_builtin_with_redirs(t_cmd *cmd, t_shell *data)
{
    int saved_stdin;
    int saved_stdout;
    int ret;

    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdin < 0 || saved_stdout < 0)
        return 1;
    if (apply_redirections(cmd))
    {
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        return 1;
    }
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
    ret = execute_builtin(data, cmd);
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    return ret;
}

/* Procura executável no PATH */
char *find_in_path(const char *cmd, char **envp)
{
    int i, j;
    char *full;
    char *path_env = env_get(envp, "PATH");
    char **paths;

    if (!path_env) return NULL;
    paths = ft_split(path_env, ':');
    if (!paths) return NULL;

    i = 0;
    while (paths[i])
    {
        full = ft_strjoin3(paths[i], "/", (char *)cmd);
        if (!access(full, X_OK))
        {
            j = 0;
            while (paths[j]) free(paths[j++]);
            free(paths);
            return full;
        }
        free(full);
        i++;
    }
    j = 0;
    while (paths[j]) free(paths[j++]);
    free(paths);
    return NULL;
}


int apply_redirections(t_cmd *cmd)
{
    t_redir *r = cmd->redirs;
    int fd;

    while (r)
    {
        if (r->type == REDIR_IN)
        {
            fd = open(r->filename, O_RDONLY);
            if (fd < 0) return (perror(r->filename), -1);
            if (cmd->input_fd != STDIN_FILENO) close(cmd->input_fd);
            cmd->input_fd = fd;
        }
        else if (r->type == REDIR_OUT)
        {
            fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) return (perror(r->filename), -1);
            if (cmd->output_fd != STDOUT_FILENO) close(cmd->output_fd);
            cmd->output_fd = fd;
        }
        else if (r->type == REDIR_APPEND)
        {
            fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) return (perror(r->filename), -1);
            if (cmd->output_fd != STDOUT_FILENO) close(cmd->output_fd);
            cmd->output_fd = fd;
        }
        else if (r->type == REDIR_DELIMITER)
        {
            if (cmd->input_fd != STDIN_FILENO) close(cmd->input_fd);
            cmd->input_fd = open(r->heredoc_path, O_RDONLY);
            if (cmd->input_fd < 0) return (perror("heredoc"), -1);
        }
        r = r->next;
    }
    return 0;
}

/* Verifica se há redirecionamento de saída */
int has_output_redirection(t_cmd *cmd)
{
    t_redir *r = cmd->redirs;
    while (r)
    {
        if (r->type == REDIR_OUT || r->type == REDIR_APPEND) return 1;
        r = r->next;
    }
    return 0;
}

/* Executa comandos externos */
int execute_external(t_shell *data, t_cmd *cmd)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0)
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
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

int execute_pipeline(t_shell *data, t_cmd *cmd_list)
{
    t_cmd *cmd;
    int status;
    int fd_in;
    int fd_pipe[2];

    cmd = cmd_list;
    fd_in = STDIN_FILENO;
    status = 0;

    while (cmd)
    {
        if (cmd->next)
            pipe(fd_pipe);

        cmd->input_fd = fd_in;
        if (cmd->next && !has_output_redirection(cmd))
            cmd->output_fd = fd_pipe[1];
        else
            cmd->output_fd = STDOUT_FILENO;

        if (cmd->is_builtin)
            status = execute_builtin_with_redirs(cmd, data);
        else
            status = execute_external(data, cmd);

        data->last_exit_status = status;

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

/* Função principal de execução */
int execute(t_shell *data)
{
    if (!data->name_cmd) return 0;
    return execute_pipeline(data, data->name_cmd);
}
