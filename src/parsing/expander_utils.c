/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:16:35 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 16:09:08 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_key_len(char *str)
{
	int	i;

	i = 1;
	if (*str == '?')
		return (1);
	if (!(*str == '_' || ft_isalpha(*str)))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*get_expanded_value(t_shell *data, char *key_start, int key_len)
{
	char	*key;
	char	*value;
	char	*result;

	if (*key_start == '?')
		return (garbage_itoa(data, data->last_exit_status));
	key = create_temp_key(key_start, key_len);
	if (!key)
		return (NULL);
	value = env_get(data->envp, key);
	free(key);
	if (value)
		result = garbage_strdup(data, value);
	else
		result = garbage_strdup(data, "");
	return (result);
}

static char	*apnd_prfx_seg(t_shell *data, char *result, char *start, char *end)
{
	char	*prefix;
	int		len;

	len = end - start;
	if (len <= 0)
		return (result);
	prefix = garbage_substr(data, start, 0, len);
	if (!prefix)
		return (NULL);
	result = garbage_strjoin(data, result, prefix);
	return (result);
}

static char	*handle_dollar(t_shell *data, char *result, char **read_ptr)
{
	int		key_len;
	char	*expanded;

	key_len = get_var_key_len(*read_ptr);
	if (key_len == 0)
	{
		result = garbage_strjoin(data, result, "$");
		(*read_ptr)++;
		return (result);
	}
	expanded = get_expanded_value(data, *read_ptr, key_len);
	if (!expanded)
		return (NULL);
	result = garbage_strjoin(data, result, expanded);
	*read_ptr += key_len;
	return (result);
}

char	*sub_var_in_str(t_shell *data, char *str)
{
	char	*result_str;
	char	*read_ptr;
	char	*next_dollar;

	result_str = garbage_strdup(data, "");
	if (!result_str)
		return (NULL);
	read_ptr = str;
	next_dollar = ft_strchr(read_ptr, '$');
	while (next_dollar != NULL)
	{
		result_str = apnd_prfx_seg(data, result_str, read_ptr, next_dollar);
		if (!result_str)
			return (NULL);
		read_ptr = next_dollar + 1;
		result_str = handle_dollar(data, result_str, &read_ptr);
		if (!result_str)
			return (NULL);
		next_dollar = ft_strchr(read_ptr, '$');
	}
	return (finalize_and_return(data, result_str, read_ptr));
}
