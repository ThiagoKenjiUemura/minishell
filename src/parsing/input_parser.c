/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* input_parser.c                                     :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/10/28 16:56:16 by tkenji-u          #+#    #+#             */
/* Updated: 2025/11/28 15:39:02 by tkenji-u         ###   ########.fr       */
/* */
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

/* [FIX] A validacao anterior (invalid_nested_same_quotes) estava incorreta.
   Ela impedia casos validos como "texto1""texto2". No Bash, aspas adjacentes
   sao permitidas e apenas concatenam as strings.
   Removemos a logica que contava grupos de aspas e retornamos false (valido),
   pois quote_parser ja garante que nao ha aspas abertas. */
bool	invalid_nested_same_quotes(const char *s)
{
	(void)s;
	return (false);
}