/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:14:57 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/26 17:59:45 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (!args)
		return (0);

	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}

	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}

	if (newline)
		write(STDOUT_FILENO, "\n", 1);

	return (0);
}
