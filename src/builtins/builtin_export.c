/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:30:09 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 08:25:15 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_shell *data, char **args)
{
	int		i;
	char	*eq;

	i = 1;
	if (!args[1])
	{
		ft_env(data, args);
		return (0);
	}
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			*eq = '\0';
			env_set(&data->envp, args[i], eq + 1);
		}
		else
			env_set(&data->envp, args[i], "");
		i++;
	}
	return (0);
}
