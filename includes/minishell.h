/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:06:27 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/22 17:25:31 by tkenji-u         ###   ########.fr       */
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
	char			*filename_or_delimiter;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
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

//Main / Setup 
int		main(int argc, char **argv, char **envp);
void	handle_sigint(int sig_num);
char	**init_envp(t_shell *data, char **envp);
void	free_shell(t_shell *data);
//Garbage
void	*garbage_calloc(t_shell *data, size_t size);
int		garbage_add(t_shell *data, void *ptr);
char	*garbage_strdup(t_shell *data, const char *src);
void	garbage_free_all(t_shell *data);
char	*garbage_substr(t_shell *data, char const *s, unsigned int start, size_t len);
char	*garbage_strjoin(t_shell *data, char const *s1, char const *s2);
//Parser / Lexer
int		count_tokens(char *input);
int		skip_spaces(char *input, int i);
t_token	*create_token(t_shell *data, char *value, t_type type);
t_type	get_token_type(char *input, int i);
void	token_add_back(t_token **head, t_token *new_node);
int		get_token_len(char *input, int i);
int		get_operator_len(char *input, int i);
int		get_quote_len(char *input, int i);
int		get_word_len(char *input, int i);
t_cmd	*parser(t_shell *data, t_token *token_list);
t_token	*lexer(t_shell *data, char *input);
bool	quote_parser(char *input);
int		ft_str_arr_len(t_cmd *cmd);
int		add_arg_to_cmd(t_shell *data, t_cmd *cmd, char *value);
int		add_redir_to_cmd(t_shell *data, t_cmd *cmd, t_token *op_token, t_token *file_token);
char    *substitute_var_in_string(t_shell *data, char *str);
int		expand_tokens(t_shell *data, t_token *head);
// Builtins
int		execute(t_shell *data);
int		is_builtin(char *cmd);
int		ft_exit(t_shell *shell, t_cmd *cmd);
int		ft_cd(char **args);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_export(t_shell *data, char **args);
char	*env_get(char **env, const char *key);
int 	env_set(t_shell *data, char ***env, const char *key, const char *value);
int 	env_remove(t_shell *data, char ***env, const char *key);
int		ft_env(t_shell *data, char **args);
int		is_valid_identifier(char *str);
int		ft_unset(t_shell *data, char **args);

#endif