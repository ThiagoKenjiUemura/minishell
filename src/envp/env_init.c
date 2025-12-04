/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinpache <vinpache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:43:33 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/03 20:55:34 by vinpache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *data)
{
	if (!data)
		return ;
	garbage_free_all(data);
	if (data->envp != NULL)
	{
		free_envp(data->envp);
		data->envp = NULL;
	}
	free(data);
	data = NULL;
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
	envp = NULL;
}

char	**init_envp(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
