/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:59:13 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/03 19:49:43 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_loop(t_shell *data)
{
	while (1)
	{
		data->input = readline("minishel$ ");
		if (!data->input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*data->input)
			add_history(data->input);
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;
	
	(void)argv;
	(void)envp;
	if(!check_argc(argc))
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data = ft_calloc(1, sizeof(t_shell));
	minishell_loop(data);
	return (0);
}