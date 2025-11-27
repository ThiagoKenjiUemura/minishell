/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:25:53 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 11:28:28 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch_redir(t_cmd *cmd, t_redir *r)
{
	if (r->type == REDIR_IN)
		return (apply_infile(cmd, r));
	if (r->type == REDIR_OUT)
		return (apply_outfile(cmd, r));
	if (r->type == REDIR_APPEND)
		return (apply_append(cmd, r));
	if (r->type == REDIR_DELIMITER)
		return (apply_delimiter(cmd, r));
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (dispatch_redir(cmd, r) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
