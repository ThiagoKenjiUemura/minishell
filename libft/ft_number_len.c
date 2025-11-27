/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:50:15 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 11:57:17 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_number_len(unsigned int number)
{
	size_t	number_len;

	number_len = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number /= 10;
		number_len++;
	}
	return (number_len);
}
