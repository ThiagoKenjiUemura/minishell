/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:47:09 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/11/26 02:31:06 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_arg_to_cmd(t_shell *data, t_cmd *cmd, char *value)
{
	int		len;
	char	**new_args;
	int		i;

	if (!cmd || !value)
		return (1);
	len = 0;
	if (cmd->args)
	{
		while (cmd->args[len])
			len++;
	}
	new_args = garbage_calloc(data, sizeof(char *) * (len + 2));
	if (!new_args)
		return (1);
	i = 0;
	while (i < len)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = garbage_strdup(data, value);
	new_args[i + 1] = NULL;
	cmd->args = new_args;
	return (0);
}

int	ft_str_arr_len(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL || cmd->args == NULL)
		return (0);
	while (cmd->args[i] != NULL)
		i++;
	return (i);
}

int add_redir_to_cmd(t_shell *data, t_cmd *cmd,
					 t_token *op_token, t_token *file_token)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = garbage_calloc(data, sizeof(t_redir));
	if (!new_redir)
		return (1);
	new_redir->type = op_token->type;
	new_redir->filename_or_delimiter = file_token->value;
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
	return (0);
}
