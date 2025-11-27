/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:25:51 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/27 17:35:29 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Remove quotes exactly like Bash:
** - Single quotes: everything inside is literal.
** - Double quotes: everything inside is literal, except that expansion
**   happens later (this function only removes the quotes).
** - Multiple quoted/unquoted segments are concatenated.
*/

char    *rmv_quotes_str(t_shell *data, char *str)
{
    char    *res;
    int     i = 0;
    int     j = 0;
    char    quote = 0;

    if (!str)
        return (NULL);

    /* allocate the maximum possible size (length without quotes unknown yet) */
    res = garbage_calloc(data, ft_strlen(str) + 1);
    if (!res)
        return (NULL);

    while (str[i])
    {
        if (!quote && (str[i] == '\'' || str[i] == '\"'))
        {
            /* start a quoted block */
            quote = str[i];
        }
        else if (quote && str[i] == quote)
        {
            /* close the quoted block */
            quote = 0;
        }
        else
        {
            /* regular character OR inside quotes */
            res[j++] = str[i];
        }
        i++;
    }
    return (res);
}