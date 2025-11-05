/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:43:33 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/05 17:29:04 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static void	free_env_copy(char **copy, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	free_shell(t_shell *data)
{
	if (!data)
		return ;
	gc_free_all(data);
	if (data->envp)
		free_envp(data->envp);
	if (data->input)
		free(data->input);
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