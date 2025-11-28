/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:56:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 15:39:02 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_parser(const char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		i++;
	}
	return (quote == 0);
}

static void	skip_until_char(const char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i] == c)
		(*i)++;
}

bool	invalid_nested_same_quotes(const char *s)
{
	int	i;
	int	double_groups;
	int	single_groups;

	i = 0;
	double_groups = 0;
	single_groups = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			double_groups++;
			skip_until_char(s, &i, '"');
		}
		else if (s[i] == '\'')
		{
			single_groups++;
			skip_until_char(s, &i, '\'');
		}
		else
			i++;
	}
	if (double_groups > 1 || single_groups > 1)
		return (true);
	return (false);
}
