/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:00:11 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/22 16:47:55 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substitute_var_in_string(t_shell *data, char *str)
{
	char	*result;
	char	*read_ptr;
	char	*next_dollar;
	char	*expanded_value;
	int		prefix_len;
	int		key_len;
	
	result = NULL;
	read_ptr = str;
	while ((next_dollar = ft_strchr(read_ptr, '$')) != NULL)
	{
		prefix_len = next_dollar - read_ptr;
		if (prefix_len > 0)
		{
			char *prefix = ft_substr(read_ptr, 0, prefix_len);
			result = ft_strjoin(result, prefix);
		}
		read_ptr = next_dollar + 1;
		key_len = get_var_key_len(read_ptr);
		
		if (key_len == 0)
		{
			read_ptr--;
			break;
		}
		expanded_value = get_expanded_value(data, read_ptr, key_len);
		if (*expanded_value)
			result = ft_strjoin(result, expanded_value);
		read_ptr += key_len;
	}
	if (*read_ptr)
		result = ft_strjoin_and_free_old(result, read_ptr);
	if (!result)
		return (ft_strdup(""));
	return (result);
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