/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:43:33 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/05 17:43:53 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *data)
{
	if (!data)
		return ;
	gc_free_all(data);
	free(data);
}

char	**init_envp(t_shell *data, char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = garbage_calloc(data, sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = garbage_strdup(data, envp[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
