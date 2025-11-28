/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:54:03 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 14:13:29 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(t_shell *data, char *value, t_type type)
{
	t_token *new_node;

	if (!data || !value)
		return (NULL);
	new_node = garbage_calloc(data, sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = garbage_strdup(data, value);
	new_node->type = type;
	new_node->next = NULL;
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
int get_token_len(char *input, int i) 
{ 
	if (input[i] == '\'' || input[i] == '\"') 
		return (get_quote_len(input, i)); 
	else if (input[i] == '>' || input[i] == '<' || input[i] == '|') 
		return (get_operator_len(input, i)); 
	else 
		return (get_word_len(input, i)); 
}

int get_quote_len(char *s, int i)
{
    char quote = s[i];
    int start = i;

    i++; // pula a aspa de abertura
    while (s[i] && s[i] != quote)
        i++;

    if (s[i] == quote)
        i++;
    else
    {
        write(2, "minishell: syntax error\n", 25);
        return (-1);
    }

    return (i - start);
}
