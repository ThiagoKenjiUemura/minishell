/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:06:52 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 14:08:09 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

extern int	g_last_signal;

typedef enum e_token_types
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_DELIMITER,
}	t_type;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*filename;
	char			*heredoc_path;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*path;
	t_redir			*redirs;
	int				is_builtin;
	int				input_fd;
	int				output_fd;
	int				index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char		*input;
	char		**envp;
	int			last_exit_status;
	t_garbage	*garbage;
	t_cmd		*name_cmd;
	int			running;
}				t_shell;

// Main / Setup 
int		main(int argc, char **argv, char **envp);
// Signals
void	init_signals(void);
void	init_child_signals(void);
void	child_sigquit_handler(int sig);
void	handle_heredoc_sigint(int sig_num);
void	handle_sigint(int sig_num);
// Garbage
char	*garbage_substr(t_shell *data, char const *s,
			unsigned int start, size_t len);
char	*garbage_strjoin(t_shell *data, char const *s1, char const *s2);
char	*garbage_strdup(t_shell *data, const char *src);
char	*garbage_itoa(t_shell *data, int n);
int		garbage_add(t_shell *data, void *ptr);
void	garbage_free_all(t_shell *data);
void	*garbage_calloc(t_shell *data, size_t size);

// Lexer
int		get_operator_len(char *input, int i);
int		skip_quoted_word(char *input, int i, char quote);
int		get_word_len(char *input, int i);
t_token	*get_last_token_local(t_token *head);
int		concat_tokens_no_space(t_shell *data, t_token *last,
			char *value, int next_i);
int		process_one_token(t_shell *data, t_token **head, char *input, int i);
t_token	*lexer(t_shell *data, char *input);

// Token
int		skip_spaces(char *input, int i);
int		count_tokens(char *input);
t_token	*create_token(t_shell *data, char *value, t_type type);
t_type	get_token_type(char *input, int i);
void	token_add_back(t_token **head, t_token *new_node);
int		get_token_len(char *input, int i);
int		get_quote_len(char *s, int i);

// Parser
int		add_redir_to_cmd(t_shell *data, t_cmd *cmd,
			t_token *op_token, t_token *file_token);
int		is_assignment_token(char *token_value);
int		set_variable_in_env(t_shell *data, char *assignment);
bool	quote_parser(const char *s);
char	*rmv_quotes_and_expand(t_shell *data, char *str);
bool	invalid_nested_same_quotes(const char *s);
int		ft_str_arr_len(t_cmd *cmd);
int		add_arg_to_cmd(t_shell *data, t_cmd *cmd, char *value);
int		handle_pipe(t_shell *data, t_cmd **current_cmd, t_token *token);
t_cmd	*parser(t_shell *data, t_token *token_list);
// Heredoc
char	*generate_hd_filename(t_shell *data);
int		should_expand_delimiter(char *delim);
char	*clean_delimiter(t_shell *data, char *delim);
void	write_line(t_shell *data, int fd, char *line, int expand);
int		finish_heredoc(int stdin_backup, int return_value);
int		read_and_write_heredoc(t_shell *data, int fd,
			char *delimiter, int expand);
int		process_heredoc_file(t_shell *data, t_redir *redir);
int		handle_heredocs(t_shell *data, t_cmd *cmd_list);
// Expander
char	*create_temp_key(const char *s, size_t len);
char	*finalize_and_return(t_shell *data, char *result_str, char *read_ptr);
char	*sub_var_in_str(t_shell *data, char *str);
int		expand_tokens(t_shell *data, t_token **head);
// Execute
void	execute_child_process(t_shell *data, t_cmd *cmd);
int		execute_external(t_shell *data, t_cmd *cmd);
int		execute(t_shell *data);
char	*find_in_path(const char *cmd, char **envp);
void	handle_fds(t_cmd *cmd);
void	print_exec_error(char *cmd, char *msg);
int		setup_builtin_redirs(t_cmd *cmd);
void	check_dir_and_perm(char *path, char *cmd_name, t_shell *data);
char	*get_cmd_path(t_shell *data, char *cmd_name);
int		execute_pipeline(t_shell *data, t_cmd *cmd_list);
// Redirection
int		execute_builtin_with_redirs(t_cmd *cmd, t_shell *data, int in_child);
int		has_output_redirection(t_cmd *cmd);
int		apply_infile(t_cmd *cmd, t_redir *r);
int		apply_outfile(t_cmd *cmd, t_redir *r);
int		apply_append(t_cmd *cmd, t_redir *r);
int		apply_delimiter(t_cmd *cmd, t_redir *r);
int		apply_redirections(t_cmd *cmd);
void	wait_for_children(t_shell *data, pid_t last_pid);
// Builtins
int		replace_env_var(char **env, const char *key, char *new_var);
int		add_env_var(char ***env, char *new_var);
int		find_env_index(char **env, const char *key);
int		remove_env_at_index(char ***env, int idx);
int		ft_cd(t_shell *data, char **args);
int		ft_echo(char **args);
char	*env_get(char **env, const char *key);
int		env_set(char ***env, const char *key, const char *value);
int		env_remove(char ***env, const char *key);
int		ft_env(t_shell *data, char **args);
char	*ft_strdup_full(const char *key, const char *value);
int		ft_exit(t_shell *shell, t_cmd *cmd);
int		ft_exit_pipe(t_shell *data, t_cmd *cmd);
void	free_redirs(t_redir *r);
void	free_args(char **args);
int		ft_export(t_shell *data, char **args);
int		ft_cd(t_shell *data, char **args);
int		ft_pwd(void);
int		ft_unset(t_shell *data, char **args);
int		is_builtin(char *cmd);
int		execute_builtin(t_shell *data, t_cmd *cmd, int in_child);
// Envp
void	free_shell(t_shell *data);
void	free_envp(char **envp);
char	**init_envp(char **envp);
// Fd
void	setup_cmd_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2]);
void	cleanup_fds(t_cmd *cmd, int *fd_in, int fd_pipe[2]);
// Memory Leak
void	free_args(char **args);
void	free_redirs(t_redir *r);

#endif