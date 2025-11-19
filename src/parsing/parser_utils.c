/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:47:09 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/11/19 17:06:22 by thiagouemur      ###   ########.fr       */
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
	int		old_count;
	char	**old_args;
	char	**new_args;
	int		i;

	old_args = cmd->args;
	old_count = ft_str_arr_len(cmd);
	new_args = garbage_calloc(data, (old_count + 2) * sizeof(char *));
	if (!new_args)
		return (1);
	i = 0;
	while (i < old_count)
	{
		new_args[i] = old_args[i];
		i++;
	}
	new_args[old_count] = value;
	new_args[old_count + 1] = NULL;
	cmd->args = new_args;
	if (old_args != NULL)
		free(old_args);
	return (0);
}

int	add_redir_to_cmd(t_shell *data, t_cmd *cmd, t_token *op_token, t_token *file_token)
{
	(void)cmd;
	t_redir *new_redir;
	new_redir = garbage_calloc(data, sizeof(t_redir));
	if (!new_redir)
		return (1);
	new_redir->type = op_token->type;
	new_redir->filename_or_delimiter = file_token->value;
	return (0);
}
