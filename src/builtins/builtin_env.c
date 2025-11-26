/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:15:58 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/26 12:54:30 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(char **env, const char *key)
{
	int		i;
	int		len;

	len = ft_strlen(key);
	i = 0;

	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}


int	env_set(char ***env, const char *key, const char *value)
{
	int		i;
	int		len;
	char	*new_var;
	char	**new_env;

	len = ft_strlen(key);
	new_var = ft_strdup_full(key, value);
	if (!new_var)
		return (1);

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, len) && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return (0);
		}
		i++;
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		return (1);
	}

	for (int j = 0; j < i; j++)
		new_env[j] = (*env)[j];

	new_env[i] = new_var;
	new_env[i + 1] = NULL;

	free(*env);
	*env = new_env;
	return (0);
}
int	env_remove(char ***env, const char *key)
{
	int		i, j, len, idx;
	char	**new_env;

	len = ft_strlen(key);
	idx = -1;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, len) && (*env)[i][len] == '=')
		{
			idx = i;
			break;
		}
		i++;
	}
	if (idx == -1)
		return (0);
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (1);
	j = 0;
	for (int k = 0; (*env)[k]; k++)
	{
		if (k != idx)
			new_env[j++] = (*env)[k];
		else
			free((*env)[k]);
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	ft_env(t_shell *data, char **args)
{
	int	i = 0;

	if (args[1])
		return (0);

	while (data->envp[i])
	{
		ft_printf("%s\n", data->envp[i]);
		i++;
	}
	return (0);
}

char *ft_strdup_full(const char *key, const char *value)
{
	char	*full;
	size_t	key_len;
	size_t	value_len;

	if (!key || !value)
		return (NULL);

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);

	full = malloc(key_len + value_len + 2); // +1 para '=' e +1 para '\0'
	if (!full)
		return (NULL);

	ft_memcpy(full, key, key_len);
	full[key_len] = '=';
	ft_memcpy(full + key_len + 1, value, value_len);
	full[key_len + value_len + 1] = '\0';

	return (full);
}