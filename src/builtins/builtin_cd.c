/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:29:58 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/17 16:33:21 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, t_shell *data)
{
	char	*path;

	path = args[1];
	if (!path)
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}