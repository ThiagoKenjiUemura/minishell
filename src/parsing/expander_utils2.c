/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:54:46 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/25 16:56:03 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
