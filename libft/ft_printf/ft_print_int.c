/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:30:33 by liferrei          #+#    #+#             */
/*   Updated: 2025/08/07 11:32:27 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c);

int	ft_print_int(int num)
{
	unsigned int	num_u;
	int				count;

	count = 0;
	num_u = num;
	if (num < 0)
	{
		count += ft_print_char('-');
		num_u = -num;
	}
	if (num_u >= 10)
		count += ft_print_int(num_u / 10);
	count += ft_print_char(num_u % 10 + '0');
	return (count);
}
