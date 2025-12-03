/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:47:09 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/12/03 18:48:49 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static int	count_old_args(char **old_args)
{
	int	i;

	i = 0;
	if (!old_args)
		return (0);
	while (old_args[i])
		i++;
	return (i);
}

static int	copy_old_args(char **new_args, char **old_args, int old_count)
{
	int	i;

	i = 0;
	while (i < old_count)
	{
		new_args[i] = old_args[i];
		i++;
	}
	return (0);
}

int	add_arg_to_cmd(t_shell *data, t_cmd *cmd, char *value)
{
	int		old_count;
	char	**old_args;
	char	**new_args;

	if (!cmd || !value || !data)
		return (1);
	old_args = cmd->args;
	old_count = count_old_args(old_args);
	new_args = garbage_calloc(data, (old_count + 2) * sizeof(char *));
	if (!new_args)
		return (1);
	copy_old_args(new_args, old_args, old_count);
	new_args[old_count] = value;
	new_args[old_count + 1] = NULL;
	cmd->args = new_args;
	if (!cmd->cmd)
		cmd->cmd = new_args[0];
	cmd->is_builtin = is_builtin(cmd->cmd);
	return (0);
}

int	handle_pipe(t_shell *data, t_cmd **current_cmd, t_token *token)
{
	t_cmd	*next_cmd;

	if (!token->next || token->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	next_cmd = garbage_calloc(data, sizeof(t_cmd));
	if (!next_cmd)
		return (-1);
	(*current_cmd)->next = next_cmd;
	*current_cmd = next_cmd;
	return (0);
}
