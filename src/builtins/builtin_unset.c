/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:30:13 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/22 11:56:52 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int unset_error(char *arg)
{
	ft_printf("minishell: unset:  `%s': not a valid identifier\n", arg);
	return (1);
}

int	ft_unset(t_shell *data, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args)
	{
		return (0);
	}
	while (args[i])
	{
		if  (!is_valid_identifier(args[i]))
			status = unset_error(args[i]);
		else
			env_remove(data, &data->envp, args[i]);
		i++;	
	}
	return (status);
}