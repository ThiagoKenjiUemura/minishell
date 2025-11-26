/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:54:46 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/25 23:15:12 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_temp_key(const char *s, size_t len)
{
	char	*dup;
	size_t	i;

	if (len <= 0)
		return (NULL);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*finalize_and_return(t_shell *data, char *result_str, char *read_ptr)
{
	if (*read_ptr)
	{
		result_str = garbage_strjoin(data, result_str, read_ptr);
		if (!result_str)
			return (NULL);
	}
	if (!result_str)
		return (garbage_strdup(data, ""));
	return (result_str);
}
