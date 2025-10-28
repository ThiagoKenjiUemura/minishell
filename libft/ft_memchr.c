/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:40:10 by liferrei          #+#    #+#             */
/*   Updated: 2025/07/29 13:31:41 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		a;

	src = (const unsigned char *)s;
	a = (unsigned char)c;
	while (n--)
	{
		if (*src == a)
			return ((void *)src);
		src++;
	}
	return (NULL);
}
