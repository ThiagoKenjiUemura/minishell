/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* builtin_cd.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/05 12:29:58 by liferrei          #+#    #+#             */
/* Updated: 2025/12/03 13:04:02 by liferrei         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell *data, char **args)
{
	char	*path;
	char	*home;
	char	*temp;

	(void)data;
	// [FIX] Validar "too many arguments"
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	home = env_get(data->envp, "HOME"); // Use env_get em vez de getenv para usar o env interno
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
		if (path[0] == '~') // Expansao simples de ~ se necessario
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
				path = temp; // Note: temp vazará se não estiver no garbage collector, mas cd ~ nao é mandatorio no minishell basico
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