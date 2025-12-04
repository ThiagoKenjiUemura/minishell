/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:32:55 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 14:17:49 by liferrei         ###   ########.fr       */
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

int	process_export_with_equals(t_shell *data, char *arg, char *eq)
{
	int	status;

	status = 0;
	*eq = '\0';
	if (is_valid_identifier(arg))
		env_set(&data->envp, arg, eq + 1);
	else
	{
		*eq = '=';
		print_export_error(arg);
		status = 1;
	}
	if (*eq == '\0')
		*eq = '=';
	return (status);
}

int	process_export_without_equals(t_shell *data, char *arg)
{
	if (is_valid_identifier(arg))
	{
		if (!env_get(data->envp, arg))
			env_set(&data->envp, arg, "");
	}
	else
	{
		print_export_error(arg);
		return (1);
	}
	return (0);
}

int	ft_export(t_shell *data, char **args)
{
	int		i;
	int		status;
	char	*eq;

	i = 1;
	status = 0;
	if (!args[1])
		return (ft_env(data, args), 0);
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
			status |= process_export_with_equals(data, args[i], eq);
		else
			status |= process_export_without_equals(data, args[i]);
		i++;
	}
	return (status);
}
