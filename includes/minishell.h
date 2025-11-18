/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:06:27 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/17 18:01:00 by liferrei         ###   ########.fr       */
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

int		main(int argc, char **argv, char **envp);
bool	check_argc(int argc);
void	handle_sigint(int sig_num);
char	**init_envp(t_shell *data, char **envp);
void	free_shell(t_shell *data);
//Garbage
void	*garbage_calloc(t_shell *data, size_t size);
int		garbage_add(t_shell *data, void *ptr);
char	*garbage_strdup(t_shell *data, const char *src);
void	garbage_free_all(t_shell *data);
int		count_tokens(char *input);
int		skip_spaces(char *input, int i);
t_token	*create_token(t_shell *data, char *value, t_type type);
t_type	get_token_type(char *input, int i);
void	token_add_back(t_token **head, t_token *new_node);
int		get_token_len(char *input, int i);
int		get_operator_len(char *input, int i);
int		get_quote_len(char *input, int i);
int		get_word_len(char *input, int i);
void	fake_parser(t_shell *data);
// Builtins
int		execute(t_shell *data);
int		is_builtin(char *cmd);
int		ft_exit(t_shell *shell, t_cmd *cmd);
int		ft_cd(char **args, t_shell *data);
int		ft_env(char **envp);
int		ft_echo(char **args);
int		ft_pwd(void);
#endif