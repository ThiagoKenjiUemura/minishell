/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:56:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 14:26:44 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool quote_parser(const char *s)
{
    int i = 0;
    char quote = 0;

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

bool invalid_nested_same_quotes(const char *s)
{
    int i = 0;
    int double_groups = 0;
    int single_groups = 0;

    while (s[i])
    {
        if (s[i] == '"')
        {
            double_groups++;
            i++; // pula a aspa de abertura
            while (s[i] && s[i] != '"')
                i++;
            if (s[i] == '"')
                i++; // pula fechamento
        }
        else if (s[i] == '\'')
        {
            single_groups++;
            i++;
            while (s[i] && s[i] != '\'')
                i++;
            if (s[i] == '\'')
                i++;
        }
        else
            i++;
    }

    /* Se houver mais de um grupo de aspas do mesmo tipo no token,
       consideramos inválido para este minishell (conforme requisitos). */
    if (double_groups > 1 || single_groups > 1)
        return true;
    return false;
}