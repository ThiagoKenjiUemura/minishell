/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:56:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/27 16:19:07 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool quote_parser(char *input)
{
	int		i;
	bool	is_open;
	char	quote;
	int		count_quotes;

	if (!input)
		return (true);
	i = 0;
	is_open = false;
	count_quotes = 0;
	while (input[i] != '\0')
	{
		if (!is_open && (input[i] == '\'' || input[i] == '"'))
		{
			is_open = true;
			quote = input[i];
			count_quotes++;
		}
		else if (is_open && input[i] == quote)
		{
			is_open = false;
			count_quotes++;
		}
		i++;
	}
	return (count_quotes % 2 == 0);
}
