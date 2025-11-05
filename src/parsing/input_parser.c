/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:56:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/03 19:20:21 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_argc(int argc)
{
	if (argc != 1)
	{
		printf("Minishell does not accept arguments \n");
		return (false);
	}
	return (true);
}
