/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:56:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/22 16:14:03 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	quote_parser(char *input)
{
	int		i;
	bool	is_open;
	char	quote;
	int		count_quotes;

	count_quotes = 0;
	is_open = false;
	i = 0;
	while (input[i++] != '\0')
	{
		if ((is_open == false) && (input[i] == '\'' || input[i] == '\"'))
		{
			is_open = true;
			quote = input[i];
			count_quotes++;
		}
		else if (input[i] == quote)
		{
			is_open = false;
			count_quotes++;
		}
	}
	ft_printf("DEBUG: %d\n", count_quotes);
	return (count_quotes % 2 == 0);
}
