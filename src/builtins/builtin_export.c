/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:32:55 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 13:36:25 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_export(t_shell *data, char **args)
{
	int		i;
	int		status;
	char	*eq;

	i = 1;
	status = 0;
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
			if (is_valid_identifier(args[i]))
				env_set(&data->envp, args[i], eq + 1);
			else
			{
				*eq = '=';
				print_export_error(args[i]);
				status = 1;
			}
			if (*eq == '\0')
				*eq = '=';
		}
		else
		{
			if (is_valid_identifier(args[i]))
			{
				if (!env_get(data->envp, args[i]))
					env_set(&data->envp, args[i], "");
			}
			else
			{
				print_export_error(args[i]);
				status = 1;
			}
		}
		i++;
	}
	return (status);
}
