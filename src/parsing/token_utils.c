/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:54:03 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/17 16:51:27 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_shell *data, char *value, t_type type)
{
	t_token	*new_node;

	new_node = garbage_calloc(data, sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	return (new_node);
}

t_type	get_token_type(char *input, int i)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (REDIR_APPEND);
		return (REDIR_OUT);
	}
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (REDIR_DELIMITER);
		return (REDIR_IN);
	}
	if (input[i] == '|')
		return (PIPE);
	if (input[i] == '\'' || input[i] == '\"')
		return (WORD);
	return (WORD);
}
void	token_add_back(t_token **head, t_token *new_node)
{
	t_token	*current;

	current = *head;
	if (!head || !new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

int	get_token_len(char *input, int i)
{
	if (input[i] == '\'' || input[i] == '\"')
		return (get_quote_len(input, i));
	else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		return (get_operator_len(input, i));
	else
		return (get_word_len(input, i));
}
