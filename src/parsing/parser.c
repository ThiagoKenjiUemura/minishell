/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:53:38 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/18 16:37:02 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_str_arr_len(t_cmd *cmd)
{
	int i;
	
	i = 0;
	if (cmd == NULL || cmd->args == NULL)
		return (0);
	while(cmd->args[i] != NULL)
		i++;
	return (i);
}

int	add_arg_to_cmd(t_shell *data, t_cmd *cmd, char *value)
{
	cmd->args = garbage_calloc(data, sizeof(t_cmd));
	
}

t_cmd	*parser(t_shell *data, t_token *token_list)
{
	t_cmd	*head_cmd;
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_token	*current_token;

	next_cmd = garbage_calloc(data, sizeof(t_cmd));
	current_cmd = garbage_calloc(data, sizeof(t_cmd));
	head_cmd = current_cmd;
	current_token = token_list;
	if (current_token && current_token->type == PIPE)
		return (NULL);
	while (current_token != NULL)
	{
		if (current_token->type == PIPE)
		{
			current_cmd->next = next_cmd;
			current_cmd = next_cmd;
		}
		if (current_token->type == WORD)
		{
			current_cmd->args = current_token->value;
			
		}
		if (current_token->type == REDIR_DELIMITER)
		{
			
		}
		current_token = current_token->next;
	}
	return (head_cmd);
}
