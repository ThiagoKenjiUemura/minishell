/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* expander.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/22 15:00:11 by tkenji-u          #+#    #+#             */
/* Updated: 2025/11/28 15:31:50 by tkenji-u         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

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

static int	has_quotes(char *s)
{
	while (s && *s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}

int	expand_tokens(t_shell *data, t_token **head)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;
	char	*orig_val;

	if (!data || !head)
		return (-1);
	curr = *head;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->type == WORD)
		{
			orig_val = curr->value;
			if (process_word(data, curr) < 0)
				return (-1);
			// Se o token ficou vazio e nao tinha aspas, remove da lista
			if (curr->value[0] == '\0' && !has_quotes(orig_val))
			{
				if (prev)
					prev->next = next;
				else
					*head = next;
				curr = next;
				continue ;
			}
		}
		prev = curr;
		curr = next;
	}
	return (0);
}