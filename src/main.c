/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:59:13 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/22 14:56:00 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_commands(t_shell *data, t_token **tokens, t_cmd **cmd_list)
{
	*tokens = lexer(data, data->input);
	if (!*tokens)
	{
		garbage_free_all(data);
		return (0);
	}
	*cmd_list = parser(data, *tokens);
	if (!*cmd_list)
	{
		garbage_free_all(data);
		return (0);
	}
	return (1);
}

static void	minishell_loop(t_shell *data)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	while (data->running)
	{
		data->input = readline("minishell$ ");
		if (!data->input)
		{
			ft_printf("exit\n");
			data->running = 0;
			break;
		}
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

static	void init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;

	(void)argv;
	if (!check_argc(argc))
		return (1);
	init_signals();
	data = ft_calloc(1, sizeof(t_shell));
	if (!data)
		return (1);
	data->garbage = NULL;
	data->running = 1;
	data->name_cmd = NULL;
	data->envp = init_envp(data, envp);
	if (!data->envp)
	{
		garbage_free_all(data);
		free(data);
		return (1);
	}
	minishell_loop(data);
	free_shell(data);
	return (data->last_exit_status);
}
