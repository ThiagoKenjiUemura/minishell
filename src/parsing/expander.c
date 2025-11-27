/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:00:11 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/27 09:05:04 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expansion_logic(t_shell *data, t_token *token)
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
			if (handle_expansion_logic(data, current) != 0)
				return (-1);
			current->value = rmv_quotes_str(data, current->value);
			if (!current->value)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
