/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:58:11 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 11:00:29 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_commands(t_shell *data, t_token **tokens, t_cmd **cmd_list)
{
	*tokens = lexer(data, data->input);
	if (!*tokens)
		return (0);
	if (expand_tokens(data, tokens) != 0)
		return (0);
	*cmd_list = parser(data, *tokens);
	if (!*cmd_list || handle_heredocs(data, *cmd_list) != 0)
		return (0);
	return (1);
}

static void	minishell_loop(t_shell *data)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	tokens = NULL;
	cmd_list = NULL;
	while (data->running)
	{
		data->input = readline("minishell$ ");
		if (!data->input)
		{
			ft_printf("exit\n");
			data->running = 0;
			break ;
		}
		garbage_add(data, data->input);
		if (*data->input)
			add_history(data->input);
		if (prepare_commands(data, &tokens, &cmd_list))
		{
			data->name_cmd = cmd_list;
			execute(data);
		}
		garbage_free_all(data);
	}
}

static void	clean_inherited_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;
	int		exit_code;

	(void)argv;
	(void)argc;
	clean_inherited_fds();
	init_signals();
	data = ft_calloc(1, sizeof(t_shell));
	if (!data)
		return (1);
	data->garbage = NULL;
	data->running = 1;
	data->name_cmd = NULL;
	data->envp = init_envp(envp);
	if (!data->envp)
	{
		garbage_free_all(data);
		free(data);
		return (1);
	}
	minishell_loop(data);
	exit_code = data->last_exit_status;
	free_shell(data);
	return (exit_code);
}
