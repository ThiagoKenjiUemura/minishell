/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:29:58 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/03 13:04:02 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell *data, char **args)
{
	char	*path;
	char	*home;
	char	*temp;

	(void)data;

	home = getenv("HOME");
	if (!args[1])
	{
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
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
				ft_printf("cd: HOME not set\n");
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
		perror("cd");
		return (1);
	}
	return (0);
}

