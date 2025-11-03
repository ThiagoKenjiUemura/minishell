/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:31:07 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/11/03 19:49:59 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig_num)
{
	(void)sig_num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}