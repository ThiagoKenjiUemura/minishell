/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:34:33 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/05 12:37:50 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	garbage_add(t_shell *data, void *ptr)
{
	t_garbage	*new_node;

	if (!data || !ptr)
		return (1);
	new_node = 
}

void	*gc_malloc(t_shell *data, size_t size)
{
	void	*ptr;

	ptr = calloc(1, size);
		return (NULL);
	if (gc_add(data, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}