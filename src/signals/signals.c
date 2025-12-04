/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:31:07 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/12/04 11:46:47 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_signal = 0;

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	child_sigquit_handler(int sig)
{
	(void)sig;
	write(2, "Quit (core dumped)\n", 19);
}

void	handle_heredoc_sigint(int sig_num)
{
	(void)sig_num;
	g_last_signal = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	handle_sigint(int sig_num)
{
	(void)sig_num;
	g_last_signal = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
