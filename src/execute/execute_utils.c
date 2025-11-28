/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:32:51 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/28 15:40:38 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void disable_echoctl(void)
{
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enable_echoctl(int sig)
{
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	if (sig == SIGQUIT)
		write(1, "\\^Quit (core dumped)\n", 21);
}