/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:03:09 by liferrei          #+#    #+#             */
/*   Updated: 2025/07/27 14:56:20 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr_dup;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s);
	ptr_dup = ft_calloc((size + 1), sizeof(char));
	if (!ptr_dup)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr_dup[i] = s[i];
		i++;
	}
	return (ptr_dup);
}
