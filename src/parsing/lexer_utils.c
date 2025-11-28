/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:39:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 15:45:25 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator_len(char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (2);
	if (input[i] == '>')
		return (1);
	if (input[i] == '<' && input[i + 1] == '<')
		return (2);
	if (input[i] == '<')
		return (1);
	if (input[i] == '|')
		return (1);
	return (0);
}

int	skip_quoted_word(char *input, int i, char quote)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
}

int	get_word_len(char *input, int i)
{
	int		start;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '<'
		&& input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quoted_word(input, i, input[i]);
		else
			i++;
	}
	return (i - start);
}

t_token	*get_last_token_local(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	concat_tokens_no_space(t_shell *data, t_token *last,
			char *value, int next_i)
{
	char	*joined;

	joined = garbage_strjoin(data, last->value, value);
	if (!joined)
		return (-1);
	last->value = joined;
	return (next_i);
}
