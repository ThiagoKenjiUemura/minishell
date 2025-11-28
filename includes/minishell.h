/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:06:27 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 15:44:51 by tkenji-u         ###   ########.fr       */
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
# include <sys/wait.h>

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
void	handle_sigint(int sig_num);
char	**init_envp(char **envp);
// Garbage
void	*garbage_calloc(t_shell *data, size_t size);
int		garbage_add(t_shell *data, void *ptr);
char	*garbage_strdup(t_shell *data, const char *src);
void	garbage_free_all(t_shell *data);
char	*garbage_substr(t_shell *data, char const *s,
			unsigned int start, size_t len);
char	*garbage_strjoin(t_shell *data, char const *s1,
			char const *s2);
char	*garbage_itoa(t_shell *data, int n);
// Lexer
t_token	*lexer(t_shell *data, char *input);
int		get_operator_len(char *input, int i);
int		skip_quoted_word(char *input, int i, char quote);
int		get_word_len(char *input, int i);
t_token	*get_last_token_local(t_token *head);
int		concat_tokens_no_space(t_shell *data, t_token *last, char *value, int next_i);
int		skip_spaces(char *input, int i);
int		get_token_len(char *input, int i);
int		get_quote_len(char *input, int i);
int		is_assignment_token(char *token_value);
int		set_variable_in_env(t_shell *data, char *assignment);
t_type	get_token_type(char *input, int i);
// Token
int		expand_tokens(t_shell *data, t_token *head);
int add_arg_to_cmd(t_shell *data, t_cmd *cmd, char *value);
char	*rmv_quotes_and_expand(t_shell *data, char *str);
char	*sub_var_in_str(t_shell *data, char *str);
t_token	*create_token(t_shell *data, char *value, t_type type);
int		count_tokens(char *input);
void	token_add_back(t_token **head, t_token *new_node);
// Parser
t_cmd	*parser(t_shell *data, t_token *token_list);
int		add_redir_to_cmd(t_shell *data, t_cmd *cmd,
			t_token *op_token, t_token *file_token);
int		ft_str_arr_len(t_cmd *cmd);
bool	invalid_nested_same_quotes(const char *str);
bool	invalid_nested_same_quotes(const char *str);
//Heredoc
int		handle_heredocs(t_shell *data, t_cmd *cmd_list);
int		process_heredoc_file(t_shell *data, t_redir *redir);
bool	quote_parser(const char *input);
char	*create_temp_key(const char *s, size_t len);
char	*finalize_and_return(t_shell *data, char *result_str, char *read_ptr);
char	*generate_hd_filename(t_shell *data);
int		should_expand_delimiter(char *delim);
char	*clean_delimiter(t_shell *data, char *delim);
void	write_line(t_shell *data, int fd, char *line, int expand);
int		read_and_write_heredoc(t_shell *data, int fd, char *delimiter, int expand);
//Execute
int		execute(t_shell *data);
int		execute_external(t_shell *data, t_cmd *cmd);
char	*find_in_path(const char *cmd, char **envp);
//Redirection
int		has_output_redirection(t_cmd *cmd);
int		apply_redirections(t_cmd *cmd);
int		execute_builtin_with_redirs(t_cmd *cmd, t_shell *data);
int		apply_infile(t_cmd *cmd, t_redir *r);
int		apply_outfile(t_cmd *cmd, t_redir *r);
int		apply_append(t_cmd *cmd, t_redir *r);
int		apply_delimiter(t_cmd *cmd, t_redir *r);
// Builtins
int		is_builtin(char *cmd);
int		execute_builtin(t_shell *data, t_cmd *cmd);
int		ft_exit(t_shell *shell, t_cmd *cmd);
int		ft_cd(t_shell *data, char **args);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_unset(t_shell *data, char **args);
int		env_remove(char ***env, const char *key);
int		find_env_index(char **env, const char *key);
int		remove_env_at_index(char ***env, int idx);
int		ft_export(t_shell *data, char **args);
int		ft_env(t_shell *data, char **args);
int		env_set(char ***env, const char *key, const char *value);
char	*ft_strdup_full(const char *key, const char *value);
int		replace_env_var(char **env, const char *key, char *new_var);
int		add_env_var(char ***env, char *new_var);
char	*env_get(char **env, const char *key);
// Memory Leak
void	free_envp(char **envp);
void	free_shell(t_shell *data);
#endif