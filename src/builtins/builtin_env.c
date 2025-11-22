/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:15:58 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/22 12:34:27 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(char **env, const char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*env_build_var(t_shell *data, const char *key, const char *value)
{
	size_t	total;
	char	*var;

	total = ft_strlen(key) + ft_strlen(value) + 2;
	var = garbage_calloc(data, total);
	if (!var)
		return (NULL);
	ft_strlcpy(var, key, total);
	ft_strlcat(var, "=", total);
	ft_strlcat(var, value, total);
	return (var);
}

int	env_set(t_shell *data, char ***env, const char *key, const char *value)
{
	int		i;
	int		len;
	char	*new_var;
	char	**new_env;

	i = 0;
	len = ft_strlen(key);
	new_var = env_build_var(data, key, value);
	if (!new_var)
		return (1);
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, len) && (*env)[i][len] == '=')
		{
			(*env)[i] = new_var;
			return (0);
		}
		i++;
	}
	new_env = garbage_calloc(data, sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	*env = new_env;
	return (0);
}

int	env_remove(t_shell *data, char ***env, const char *key)
{
	int		i;
	int		j;
	int		len;
	int		count;
	char	**new_env;

	i = 0;
	j = 0;
	len = ft_strlen(key);
	count = 0;
	while ((*env)[count])
		count++;
	new_env = garbage_calloc(data, sizeof(char *) * count);
	if (!new_env)
		return (1);
	while ((*env)[i])
	{
		if (!(ft_strncmp((*env)[i], key, len) == 0 && (*env)[i][len] == '='))
		{
			new_env[j] = (*env)[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	*env = new_env;
	return (0);
}

int	ft_env(t_shell *data, char **args)
{
	int	i;

	i = 0;
	if (args[1] != NULL)
		return (0);
	while (data->envp[i])
	{
		ft_printf("%s\n", data->envp[i]);
		i++;
	}
	return (0);
}
