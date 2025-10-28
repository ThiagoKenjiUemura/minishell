/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:16:49 by liferrei          #+#    #+#             */
/*   Updated: 2025/07/29 10:56:54 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	len;
	size_t	i;

	i = 0;
	src_len = 0;
	src_len = ft_strlen(src);
	len = src_len;
	if (size == 0)
		return (src_len);
	if (src_len >= size)
		len = size - 1;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[len] = '\0';
	return (src_len);
}
