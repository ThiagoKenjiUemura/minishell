/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:10:10 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/12/03 13:37:54 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

static int	skip_quotes(char *input, int i)
{
	char	quote_type;

	quote_type = input[i];
	i++;
	while (input[i] != '\0' && input[i] != quote_type)
		i++;
	if (input[i] == quote_type)
		i++;
	return (i);
}

static int	skip_operator(char *input, int i)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			i += 2;
		else
			i++;
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			i += 2;
		else
			i++;
	}
	else if (input[i] == '|')
		i++;
	return (i);
}

static int	skip_word(char *input, int i)
{
	while (input[i] != '\0' && input[i] != ' '
		&& input[i] != '|' && input[i] != '<' && input[i] != '>'
		&& input[i] != '\'' && input[i] != '\"')
		i++;
	return (i);
}

int	count_tokens(char *input)
{
	int		count_tokens;
	int		i;

	i = 0;
	count_tokens = 0;
	while (input[i] != '\0')
	{
		i = skip_spaces(input, i);
		if (input[i] == '\0')
			break ;
		count_tokens++;
		if (input[i] == '\"' || input[i] == '\'')
			i = skip_quotes(input, i);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>' )
			i = skip_operator(input, i);
		else
			i = skip_word(input, i);
	}
	return (count_tokens);
}
