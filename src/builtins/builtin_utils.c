/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:37:19 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 11:43:36 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_env_var(char **env, const char *key, char *new_var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_env_var(char ***env, char *new_var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (free(new_var), 1);
	j = 0;
	while (j < i)
	{
		new_env[j] = (*env)[j];
		j++;
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	find_env_index(char **env, const char *key)
{
	int	i;
	int	len;

	if (!env || !key)
		return (-1);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**copy_env_except_index(char **env, int idx)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	j = 0;
	i = 0;
	while (env[i])
	{
		if (i != idx)
			new_env[j++] = env[i];
		else
			free(env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	remove_env_at_index(char ***env, int idx)
{
	char	**new_env;

	if (!env || !*env || idx < 0)
		return (0);
	new_env = copy_env_except_index(*env, idx);
	if (!new_env)
		return (1);
	free(*env);
	*env = new_env;
	return (0);
}
