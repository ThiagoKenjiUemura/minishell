/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:59:13 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/10/28 17:43:56 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_loop(t_shell *data)
{
	while(1)
	{
		data->input = readline("minishel> ");
		if (!data->input)
			break ;
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;
	
	data = ft_calloc(1, sizeof(t_shell));
	(void)argv;
	(void)argc;
	(void)envp;
	minishell_loop(data);
}