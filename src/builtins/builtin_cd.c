/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:07 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 14:18:25 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_too_many_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static char	*expand_home(char *path, char *home)
{
	char	*temp;

	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	if (path[1] == '\0')
		return (home);
	temp = ft_strjoin(home, path + 1);
	return (temp);
}

char	*cd_get_target_path(t_shell *data, char **args)
{
	char	*home;
	char	*path;

	home = env_get(data->envp, "HOME");
	if (!args[1])
	{
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home);
	}
	path = args[1];
	if (path[0] == '~')
		return (expand_home(path, home));
	return (path);
}

static int	cd_change_directory(char *path)
{
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

int	ft_cd(t_shell *data, char **args)
{
	char	*path;

	if (handle_too_many_args(args))
		return (1);
	path = cd_get_target_path(data, args);
	if (!path)
		return (1);
	return (cd_change_directory(path));
}
