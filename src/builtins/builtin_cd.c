/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:07 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 13:36:13 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell *data, char **args)
{
	char	*path;
	char	*home;
	char	*temp;

	(void)data;
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	home = env_get(data->envp, "HOME");
	if (!args[1])
	{
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		path = home;
	}
	else
	{
		path = args[1];
		if (path[0] == '~')
		{
			if (!home)
			{
				ft_putstr_fd("minishell: cd: HOME not set\n", 2);
				return (1);
			}
			if (path[1] == '\0')
				path = home;
			else
			{
				temp = ft_strjoin(home, path + 1);
				path = temp;
			}
		}
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}
