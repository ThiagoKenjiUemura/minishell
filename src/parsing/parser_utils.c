/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:47:09 by thiagouemur       #+#    #+#             */
/*   Updated: 2025/11/27 16:25:59 by thiagouemur      ###   ########.fr       */
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

int	add_arg_to_cmd(t_shell *data, t_cmd *cmd, char *value)
{
	int		old_count;
	char	**old_args;
	char	**new_args;
	int		i;

	i = 0;
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
	if (cmd->cmd == NULL)
		cmd->cmd = new_args[0];
	cmd->is_builtin = is_builtin(cmd->cmd);
	return (0);
}

static char *clean_token_value(t_shell *data, char *s)
{
	int len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if ((s[0] == '\'' && s[len - 1] == '\'')
		|| (s[0] == '"' && s[len - 1] == '"'))
		return (garbage_substr(data, s, 1, len - 2));
	return (garbage_strdup(data, s));
}

int add_redir_to_cmd(t_shell *data, t_cmd *cmd, t_token *op_token, t_token *file_token)
{
	t_redir *new_redir;

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
	/* add to cmd->redirs list */
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		t_redir *tmp = cmd->redirs;
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
	return ret;
}