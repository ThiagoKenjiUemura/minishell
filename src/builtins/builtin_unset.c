/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:30:13 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 08:25:44 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *data, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		env_remove(&data->envp, args[i]);
		i++;
	}
	return (0);
}
