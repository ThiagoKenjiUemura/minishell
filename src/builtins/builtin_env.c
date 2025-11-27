/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:15:58 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 11:39:26 by liferrei         ###   ########.fr       */
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
	char	*new_var;

	new_var = ft_strdup_full(key, value);
	if (!new_var)
		return (1);
	if (replace_env_var(*env, key, new_var))
		return (0);
	return (add_env_var(env, new_var));
}

int	env_remove(char ***env, const char *key)
{
	int	idx;

	idx = find_env_index(*env, key);
	if (idx == -1)
		return (0);
	return (remove_env_at_index(env, idx));
}

int	ft_env(t_shell *data, char **args)
{
	int	i;

	i = 0;
	if (args[1])
		return (0);
	while (data->envp[i])
	{
		ft_printf("%s\n", data->envp[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup_full(const char *key, const char *value)
{
	char	*full;
	size_t	key_len;
	size_t	value_len;

	if (!key || !value)
		return (NULL);
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	full = malloc(key_len + value_len + 2);
	if (!full)
		return (NULL);
	ft_memcpy(full, key, key_len);
	full[key_len] = '=';
	ft_memcpy(full + key_len + 1, value, value_len);
	full[key_len + value_len + 1] = '\0';
	return (full);
}
