/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:53:38 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/22 11:48:11 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_pipe(t_shell *data, t_cmd **current_cmd, t_token *token)
{
	t_cmd	*next_cmd;

	if (!token->next || token->next->type == PIPE)
		return (1);
	next_cmd = garbage_calloc(data, sizeof(t_cmd));
	if (!next_cmd)
		return (1);
	(*current_cmd)->next = next_cmd;
	*current_cmd = next_cmd;
	return (0);
}

static int	process_token_type(t_shell *data, t_cmd *cmd, t_token *token)
{
	if (token->type >= REDIR_IN && token->type <= REDIR_DELIMITER)
	{
		if (!token->next || token->next->type != WORD)
			return (-1);
		if (add_redir_to_cmd(data, cmd, token, token->next) != 0)
			return (-1);
		return (2);
	}
	else if (token->type == WORD)
	{
		if (add_arg_to_cmd(data, cmd, token->value) != 0)
			return (-1);
		return (1);
	}
	return (1);
}

static t_cmd	*init_parser_head(t_shell *data, t_token *list, t_cmd **current_cmd)
{
	t_cmd *head;

	if (list && list->type == PIPE)
		return (NULL);
	head = garbage_calloc(data, sizeof(t_cmd));
	if (!head)
		return (NULL);
	*current_cmd = head;
	
	return (head);
}

t_cmd	*parser(t_shell *data, t_token *token_list)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*current_token;
	int		advance;

	cmd_list = init_parser_head(data, token_list, &current_cmd);
	if (!cmd_list)
		return (NULL);
	current_token = token_list;
	while (current_token != NULL)
	{
		if (current_token->type == PIPE)
		{
			if (handle_pipe(data, &current_cmd, current_token) != 0)
				return (NULL);
			current_token = current_token->next;
			continue;
		}
		advance = process_token_type(data, current_cmd, current_token);
		if (advance == -1)
			return (NULL);
		while (advance-- > 0)
			current_token = current_token->next;
	}
	return (cmd_list);
}
