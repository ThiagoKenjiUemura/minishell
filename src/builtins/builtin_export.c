/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:30:09 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/19 14:59:43 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static 
int	ft_export(char **args, t_shell *data, char **envp)
{
	int		i;
	char	**env_copy;
	
	i = 0;
	if (args[1])
		return (0);
	env_copy = init_envp(data, envp);
	if (!env_copy)
	{
		garbage_free_all(data);
		free(data);
		return (1);
	}
	ft_sort_env(env_copy);
	while (env_copy[i])
	{
		ft_print("declare -x %s\n", env_copy[i]);
		i++;
	}
	free_shell(data);
}
