/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:00:11 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 15:31:50 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_expansion_logic(t_shell *data, t_token *token)
{
	char	*new_value;

	if (!token || !token->value)
		return (-1);
	if (token->value[0] == '\'')
		return (0);
	if (ft_strchr(token->value, '$'))
	{
		new_value = sub_var_in_str(data, token->value);
		if (!new_value)
			return (-1);
		token->value = new_value;
	}
	return (0);
}

static int	is_invalid_word(char *value)
{
	if (!quote_parser(value))
		return (1);
	if (invalid_nested_same_quotes(value))
		return (1);
	return (0);
}

static int	process_word(t_shell *data, t_token *token)
{
	char	*tmp;

	if (is_invalid_word(token->value))
	{
		write(2, "minishell: syntax error\n", 25);
		return (-1);
	}
	tmp = rmv_quotes_and_expand(data, token->value);
	if (!tmp)
		return (-1);
	token->value = tmp;
	return (0);
}

int	expand_tokens(t_shell *data, t_token *head)
{
	t_token	*current;

	if (!data || !head)
		return (-1);
	current = head;
	while (current)
	{
		if (current->type == WORD)
		{
			if (process_word(data, current) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
