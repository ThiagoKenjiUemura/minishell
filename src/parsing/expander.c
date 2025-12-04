/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:07:55 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/04 10:10:08 by tkenji-u         ###   ########.fr       */
/*                                                                            */
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

static int	handle_word_expansion(t_shell *data, t_token **curr,
		t_token **prev, t_token **head)
{
	char	*orig_val;
	t_token	*next;

	next = (*curr)->next;
	orig_val = (*curr)->value;
	if (process_word(data, *curr) < 0)
		return (-1);
	if ((*curr)->value[0] == '\0' && !has_quotes(orig_val))
	{
		if (*prev)
			(*prev)->next = next;
		else
			*head = next;
		*curr = next;
		return (1);
	}
	*prev = *curr;
	*curr = next;
	return (0);
}

int	expand_tokens(t_shell *data, t_token **head)
{
	t_token	*curr;
	t_token	*prev;
	int		status;

	if (!data || !head)
		return (-1);
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->type == WORD)
		{
			status = handle_word_expansion(data, &curr, &prev, head);
			if (status == -1)
				return (-1);
			if (status == 1)
				continue ;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (0);
}
