/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:00:11 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/22 15:32:48 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substitute_var_in_string(t_shell *data, char *str)
{
	char	*final_str;
	char	*read_ptr;
	char    *next_dollar;
	
	final_str = NULL;
	read_ptr = str;
	while ((next_dollar = ft_strchr(read_ptr, '$')) != NULL)
	{
		
		next_dollar++;
	}
	return (final_str);
}

void	expand_tokens(t_shell *data, t_token *head)
{
	t_token	*current_token;

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
			current_token->value = substitute_var_in_string(data, current_token->value);
		}
		current_token = current_token->next;
	}
}