/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:34:33 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 15:20:26 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	garbage_add(t_shell *data, void *ptr)
{
	t_garbage	*new_node;

	if (!data || !ptr)
		return (1);
	new_node = ft_calloc(1, sizeof(t_garbage));
	if (!new_node)
		return (1);
	new_node->ptr = ptr;
	new_node->next = data->garbage;
	data->garbage = new_node;
	return (0);
}

void	garbage_free_all(t_shell *data)
{
	t_garbage *tmp;

	if (!data)
		return ;
	while (data->garbage != NULL)
	{
		tmp = data->garbage;
		data->garbage = data->garbage->next;
		if (tmp->ptr != NULL)
		{
			free(tmp->ptr);
			tmp->ptr = NULL;
		}
		free(tmp);
	}
	data->garbage = NULL;
}

void	*garbage_calloc(t_shell *data, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(1, size);
	if (!ptr)
		return (NULL);
	if (garbage_add(data, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
