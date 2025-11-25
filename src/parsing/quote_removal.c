/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:25:51 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/25 16:37:41 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_clean_len(char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
			len++;
		str++;
	}
	return (len);
}

char	*rmv_quotes_str(t_shell *data, char *str)
{
	size_t	final_lenght;
	char	*new_str;
	char	*dest_ptr;
	char	*original_str;

	original_str = str;
	final_lenght = get_clean_len(original_str);
	new_str = garbage_calloc(data, final_lenght + 1);
	if (!new_str)
		return (NULL);
	dest_ptr = new_str;
	str = original_str;
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
		{
			*dest_ptr = *str;
			dest_ptr++;
		}
		str++;
	}
	return (new_str);
}
