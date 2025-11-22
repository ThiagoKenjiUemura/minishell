/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:00:11 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/22 17:24:31 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_tokens(t_shell *data, t_token *head)
{
	t_token	*current_token;
	char	*new_value;

	current_token = head;
	while (current_token != NULL)
	{
		if (current_token->value[0] == '\'')
		{
			current_token = current_token->next;
			continue;
		}
		else if(ft_strchr(current_token->value, '$'))
		{
			new_value = substitute_var_in_string(data, current_token->value);

			if (!new_value)
				return (-1);
				
			current_token->value = new_value; 
		}
		current_token = current_token->next;
	}
	return (0);
}
