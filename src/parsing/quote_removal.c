/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:25:51 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 17:22:24 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*safe_join(t_shell *data, char *a, char *b)
{
	char	*tmp;

	if (!a && !b)
		return (garbage_strdup(data, ""));
	if (!a)
		a = garbage_strdup(data, "");
	if (!b)
		b = "";
	tmp = garbage_strjoin(data, a, b);
	return (tmp);
}

static char	*process_single_quotes(t_shell *data, char *str, int *i)
{
	int		start;
	char	*tmp;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	tmp = garbage_substr(data, str, start, *i - start);
	if (str[*i] == '\'')
		(*i)++;
	return (tmp);
}

static char	*process_double_quotes(t_shell *data, char *str, int *i)
{
	int		start;
	char	*tmp;
	char	*expanded;

	start = ++(*i);
	while (str[*i] && str[*i] != '"')
		(*i)++;
	tmp = garbage_substr(data, str, start, *i - start);
	if (str[*i] == '"')
		(*i)++;
	expanded = sub_var_in_str(data, tmp);
	if (!expanded)
		expanded = garbage_strdup(data, "");
	return (expanded);
}

static char	*process_plain(t_shell *data, char *str, int *i)
{
	int		start;
	char	*tmp;
	char	*expanded;

	start = *i;
	while (str[*i]
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != ' '
		&& str[*i] != '|'
		&& str[*i] != '<'
		&& str[*i] != '>')
		(*i)++;
	tmp = garbage_substr(data, str, start, *i - start);
	expanded = sub_var_in_str(data, tmp);
	if (!expanded)
		expanded = garbage_strdup(data, "");
	return (expanded);
}

char	*rmv_quotes_and_expand(t_shell *data, char *str)
{
	char	*res;
	char	*piece;
	int		i;

	res = garbage_strdup(data, "");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			piece = process_single_quotes(data, str, &i);
		else if (str[i] == '"')
			piece = process_double_quotes(data, str, &i);
		else
			piece = process_plain(data, str, &i);
		res = safe_join(data, res, piece);
	}
	return (res);
}
