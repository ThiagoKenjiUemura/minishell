/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:30:09 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/22 11:04:40 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_export_with_value(t_shell *data, char *arg)
{
	char	*equal_sign;
	int		key_len;
	char	*key;
	char	*value;
	
	equal_sign = ft_strchr(arg, '=');
	key_len = equal_sign - arg;
	key = garbage_calloc(data, key_len + 1);
	if (!key)
	{
		garbage_free_all(data);
		free(data);
		return (1);
	}
	ft_strlcpy(key, arg, key_len + 1);
	value = garbage_strdup(data, equal_sign + 1);
	if (!value)
	{
		garbage_free_all(data);
		free(data);
		return (1);
	}
	if (!is_valid_identifier(key))
	{
		ft_printf("export: `%s`: not a valid identifier\n", arg);
		return (0);
	}
	env_set(data, &data->envp, key, value);
	return (0);
}

static int	handle_export_without_value(t_shell *data, char *arg)
{
	if (!is_valid_identifier(arg))
	{
        ft_printf("export: `%s`: not a valid identifier\n", arg);
        return (0);
    }
    if (!env_get(data->envp, arg))
        env_set(data, &data->envp, arg, "");
    return (0);
}
int	ft_export(char **args, t_shell *data)
{
	int		i;
	
	i = 1;
	if (args[1])
		return (0);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
            handle_export_with_value(data, args[i]);
        else
            handle_export_without_value(data, args[i]);
		i++;
	}
	return (0);
}
