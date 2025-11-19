/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:29:58 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/19 14:20:44 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	if (!args[1])
		return (0);
	if (chdir(args[1]) != 0)
	{
		ft_printf("cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	return (0);
}
