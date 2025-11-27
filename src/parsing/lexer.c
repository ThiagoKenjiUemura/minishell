/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:39:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/27 14:24:45 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator_len(char *input, int i)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (2);
		else
			return (1);
	}
	if (input[i] == '|')
		return (1);
	return (0);
}

int	get_quote_len(char *input, int i)
{
	int		start_index;
	char	quote_type;

	start_index = i;
	quote_type = input[i];
	i++;
	while (input[i] != '\0' && input[i] != quote_type)
		i++;
	if (input[i] != quote_type)
		i++;
	return (i - start_index);
}

int	get_word_len(char *input, int i)
{
	int	start_index;

	start_index = i;
	while (input[i] != '\0' && input[i] != '>' && input[i] != '|'
		&& input[i] != '<' && input[i] != ' '
		&& input[i] != '\'' && input[i] != '\"')
		i++;
	return (i - start_index);
}

static int	process_one_token(t_shell *data, t_token **head, char *input, int i)
{
	int		len;
	t_type	type;
	char	*value;
	t_token	*new_node;

	new_node = NULL;
	len = get_token_len(input, i);
	type = get_token_type(input, i);
	value = ft_substr(input, i, len);
	if (!value)
		return (-1);
	if (garbage_add(data, value) == 1)
	{
		free(value);
		return (-1);
	}
	new_node = create_token(data, value, type);
	if (!new_node)
		return (-1);
	token_add_back(head, new_node);
	return (i + len);
}

t_token	*lexer(t_shell *data, char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		i = skip_spaces(input, i);
		if (input[i] == '\0')
			break ;
		i = process_one_token(data, &head, input, i);
		if (i == -1)
			return (NULL);
	}
	return (head);
}
