/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:06:27 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/04 15:10:38 by thiagouemur      ###   ########.fr       */
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

typedef struct	s_shell
{
	char	*input;
	char	**envp;
	int		last_exit_status;
}			t_shell;

typedef enum e_token_types
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_DELIMITER,
}	t_type;

typedef struct s_redir
{
	t_type			type;
	char			*filename_or_delimiter;
	struct s_redir  *next;
}	t_redir;

typedef struct	s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}					t_cmd;

int		main(int argc, char **argv, char **envp);
bool	check_argc(int argc);
void	handle_sigint(int sig_num);

#endif