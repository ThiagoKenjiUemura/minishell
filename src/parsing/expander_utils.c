/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:16:35 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/25 16:58:02 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_key_len(char *str_at_key)
{
	int	i;

	if (*str_at_key == '?')
		return (1);
	if (!(*str_at_key == '_' || ft_isalpha(*str_at_key)))
		return (0);
	i = 1;
	while (str_at_key[i] && (ft_isalnum(str_at_key[i]) || str_at_key[i] == '_'))
		i++;
	return (i);
}

static char	*get_expanded_value(t_shell *data, char *key_start, int key_len)
{
	char	*key;
	char	*value;

	if (*key_start == '?')
		return (ft_itoa(data->last_exit_status));
	key = ft_substr(key_start, 0, key_len);
	if (!key)
		return (NULL);
	value = env_get(data->envp, key);
	if (value)
		return (garbage_strdup(data, value));
	return (garbage_strdup(data, ""));
}

static char	*handle_sub(t_shell *data, char *result_str, char **read_cursor_ptr)
{
	int		key_len;
	char	*expanded_value;

	key_len = get_var_key_len(*read_cursor_ptr);
	if (key_len == 0)
	{
		(*read_cursor_ptr)--;
		return (result_str);
	}
	expanded_value = get_expanded_value(data, *read_cursor_ptr, key_len);
	if (!expanded_value)
		return (NULL);
	if (*expanded_value)
		result_str = garbage_strjoin(data, result_str, expanded_value);
	(*read_cursor_ptr) += key_len;
	return (result_str);
}

static char	*apnd_prfx_seg(t_shell *data, char *result_str,
char *read_cursor, char *next_dollar)
{
	char	*temp_prefix;
	int		prefix_len;

	prefix_len = next_dollar - read_cursor;
	if (prefix_len > 0)
	{
		temp_prefix = garbage_substr(data, read_cursor, 0, prefix_len);
		if (!temp_prefix)
			return (NULL);
		result_str = garbage_strjoin(data, result_str, temp_prefix);
		if (!result_str)
			return (NULL);
	}
	return (result_str);
}

char	*sub_var_in_str(t_shell *data, char *str)
{
	char	*result_str;
	char	*read_ptr;
	char	*next_dollar;

	result_str = NULL;
	read_ptr = str;
	next_dollar = ft_strchr(read_ptr, '$');
	while (next_dollar != NULL)
	{
		result_str = apnd_prfx_seg(data, result_str, read_ptr, next_dollar);
		if (!result_str && next_dollar > read_ptr)
			return (NULL);
		read_ptr = next_dollar + 1;
		result_str = handle_sub(data, result_str, &read_ptr);
		if (!result_str)
			return (NULL);
	}
	return (finalize_and_return(data, result_str, read_ptr));
}
