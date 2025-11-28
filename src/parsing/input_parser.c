/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:56:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 11:23:01 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool quote_parser(const char *input)
{
    int i = 0;
    char quote = 0;

    while (input[i])
    {
        if (!quote && (input[i] == '\'' || input[i] == '"'))
            quote = input[i]; // abre quote
        else if (quote && input[i] == quote)
            quote = 0; // fecha quote
        i++;
    }
    return quote == 0; // true se todas as aspas fechadas
}

