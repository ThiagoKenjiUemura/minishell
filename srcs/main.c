/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:59:13 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/10/28 19:14:50 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_loop(t_shell *data)
{
	while(1)
	{
		data->input = readline("minishel> ");
		if (!data->input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (data->input[0])
			add_history(data->input);
		free(data->input);
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;
	
	data = ft_calloc(1, sizeof(t_shell));
	(void)argv;
	(void)argc;
	minishell_loop(data);
}