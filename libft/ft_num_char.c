/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:48:54 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 11:49:11 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_num_char(char *s, int sign, unsigned int num, size_t len)
{
	size_t	i;

	i = len;
	while (i--)
	{
		s[i + sign] = (num % 10) + '0';
		num /= 10;
	}
	s[len + sign] = '\0';
	if (sign == 1)
		s[0] = '-';
	return (s);
}
