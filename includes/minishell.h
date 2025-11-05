/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:06:27 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/05 19:53:18 by liferrei         ###   ########.fr       */
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

typedef struct s_shell
{
	char		*input;
	char		**envp;
	int			last_exit_status;
	t_garbage	*garbage;
}				t_shell;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

int		main(int argc, char **argv, char **envp);
bool	check_argc(int argc);
void	handle_sigint(int sig_num);
char	**init_envp(t_shell *data, char **envp);
void	free_shell(t_shell *data);
void	*garbage_calloc(t_shell *data, size_t size);
char	*garbage_strdup(t_shell *data, const char *src);
int		garbage_add(t_shell *data, void *ptr);
void	garbage_free_all(t_shell *data);

#endif