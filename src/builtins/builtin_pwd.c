/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:15:41 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/17 16:41:11 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
	char buf[4096];
	if (getcwd(buf, sizeof(buf)))
	{
		ft_printf("%s\n", buf);
		return (0);
	}
	perror("pwd");
	return (1);
}
