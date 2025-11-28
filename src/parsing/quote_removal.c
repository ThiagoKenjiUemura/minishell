/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:25:51 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 14:32:06 by tkenji-u         ###   ########.fr       */
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

static char *safe_join(t_shell *data, char *a, char *b)
{
    if (!a && !b)
        return (garbage_strdup(data, ""));
    if (!a)
        a = garbage_strdup(data, "");
    if (!b)
        b = "";
    return (garbage_strjoin(data, a, b));
}

char *rmv_quotes_and_expand(t_shell *data, char *str)
{
    char *res = garbage_strdup(data, "");
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\'')   /* aspas simples → literal total */
        {
            int start = ++i;
            while (str[i] && str[i] != '\'')
                i++;

            char *tmp = garbage_substr(data, str, start, i - start);
            /* use safe_join para evitar NULLs estranhos */
            res = safe_join(data, res, tmp);

            if (str[i] == '\'')
                i++;
        }
        else if (str[i] == '"') /* aspas duplas → expande $ */
        {
            int start = ++i;
            while (str[i] && str[i] != '"')
                i++;

            char *tmp = garbage_substr(data, str, start, i - start);
            char *expanded = sub_var_in_str(data, tmp);
            if (!expanded)
                expanded = garbage_strdup(data, ""); /* segurança extra */

            res = safe_join(data, res, expanded);

            if (str[i] == '"')
                i++;
        }
        else  /* fora das aspas → expandir $ */
        {
            int start = i;
            while (str[i] &&
                str[i] != '\'' &&
                str[i] != '"'  &&
                str[i] != ' '  &&
                str[i] != '|'  &&
                str[i] != '<'  &&
                str[i] != '>')
                i++;

            char *tmp = garbage_substr(data, str, start, i - start);
            char *expanded = sub_var_in_str(data, tmp);
            if (!expanded)
                expanded = garbage_strdup(data, "");

            res = safe_join(data, res, expanded);
        }
    }
    return res;
}
