/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:59:13 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/05 19:50:55 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_loop(t_shell *data)
{
	while (1)
	{
		data->input = readline("minishell$ ");
		if (!data->input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*data->input)
			add_history(data->input);
		if (garbage_add(data, data->input))
		{
			free(data->input);
			break ;
		}
		data->input = NULL;
	}
}

static void	init_signals(void)
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

	data->envp = init_envp(data, envp);
	if (!data->envp)
	{
		garbage_free_all(data);
		free(data);
		return (1);
	}

	minishell_loop(data);
	free_shell(data); 
	return (0);
}
