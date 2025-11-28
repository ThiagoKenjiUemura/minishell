/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:25:51 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 11:24:43 by tkenji-u         ###   ########.fr       */
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
bool invalid_nested_same_quotes(const char *str)
{
    char quote = 0;
    int i = 0;

    while (str[i])
    {
        if (!quote && (str[i] == '\'' || str[i] == '"'))
            quote = str[i];
        else if (quote && str[i] == quote)
            quote = 0;
        else if (quote && ((quote == '\'' && str[i] == '\'') || (quote == '"' && str[i] == '"')))
            return true; // erro detectado
        i++;
    }
    return false;
}

char *rmv_quotes_and_expand(t_shell *data, char *str)
{
    char *res = garbage_strdup(data, "");
    char *tmp;
    int i = 0;
    char quote;

    while (str[i])
    {
        if (str[i] == '\'') // aspas simples: literal
        {
            quote = '\'';
            i++;
            int start = i;
            while (str[i] && str[i] != quote)
                i++;
            tmp = garbage_substr(data, str, start, i - start);
            printf("DEBUG: literal simples -> [%s]\n", tmp);
            res = garbage_strjoin(data, res, tmp);
            if (str[i] == quote)
                i++;
        }
        else if (str[i] == '"') // aspas duplas: expandir $
        {
            quote = '"';
            i++;
            int start = i;
            while (str[i] && str[i] != quote)
                i++;
            tmp = garbage_substr(data, str, start, i - start);
            char *expanded = sub_var_in_str(data, tmp); // expande $VAR
            printf("DEBUG: duplas -> original [%s], expandido [%s]\n", tmp, expanded);
            res = garbage_strjoin(data, res, expanded);
            if (str[i] == quote)
                i++;
        }
        else // fora de aspas: expande $
        {
            int start = i;
            while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"' 
                   && str[i] != '|' && str[i] != '<' && str[i] != '>')
                i++;
            tmp = garbage_substr(data, str, start, i - start);
            char *expanded = sub_var_in_str(data, tmp); // expande $VAR
            printf("DEBUG: fora de aspas -> original [%s], expandido [%s]\n", tmp, expanded);
            res = garbage_strjoin(data, res, expanded);
        }
    }
    return res;
}

