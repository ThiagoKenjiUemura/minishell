/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:00:11 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/25 16:40:38 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expansion_logic(t_shell *data, t_token *token)
{
	char	*new_value;

	if (token->value[0] == '\'')
		return (0);
	if (ft_strchr(token->value, '$'))
	{
		new_value = substitute_var_in_string(data, token->value);
		if (!new_value)
			return (-1);
		token->value = new_value;
	}
	return (0);
}

int	expand_tokens(t_shell *data, t_token *head)
{
	t_token	*current_token;

	current_token = head;
	while (current_token != NULL)
	{
		if (current_token->type != WORD)
		{
			current_token = current_token->next;
			continue ;
		}
		if (handle_expansion_logic(data, current_token) != 0)
			return (-1);
		current_token->value = rmv_quotes_str(data, current_token->value);
		if (!current_token->value)
			return (-1);
		current_token = current_token->next;
	}
	return (0);
}
