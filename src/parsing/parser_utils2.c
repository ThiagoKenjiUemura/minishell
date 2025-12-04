/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:11:51 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 10:12:01 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*clean_token_value(t_shell *data, char *s)
{
	if (!s)
		return (NULL);
	return (garbage_strdup(data, s));
}

int	add_redir_to_cmd(t_shell *data, t_cmd *cmd,
				t_token *op_token, t_token *file_token)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	(void)op_token;
	if (!cmd || !file_token)
		return (1);
	new_redir = garbage_calloc(data, sizeof(t_redir));
	if (!new_redir)
		return (1);
	new_redir->type = op_token->type;
	new_redir->filename = clean_token_value(data, file_token->value);
	new_redir->heredoc_path = NULL;
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

int	is_assignment_token(char *token_value)
{
	char	*eq;

	if (!token_value)
		return (0);
	eq = ft_strchr(token_value, '=');
	if (!eq)
		return (0);
	if (eq == token_value)
		return (0);
	return (1);
}

int	set_variable_in_env(t_shell *data, char *assignment)
{
	char	*key;
	char	*value;
	char	*eq_pos;
	int		ret;

	if (!assignment || !data)
		return (1);
	eq_pos = ft_strchr(assignment, '=');
	if (!eq_pos)
		return (1);
	key = ft_substr(assignment, 0, eq_pos - assignment);
	if (!key)
		return (1);
	value = ft_strdup(eq_pos + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	ret = env_set(&data->envp, key, value);
	free(key);
	free(value);
	return (ret);
}
