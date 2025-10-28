/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:31:24 by liferrei          #+#    #+#             */
/*   Updated: 2025/08/07 11:34:20 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c);

int	ft_print_uint(unsigned int num)
{
	int	count;

	count = 0;
	if (num >= 10)
		count += ft_print_uint(num / 10);
	count += ft_print_char(num % 10 + '0');
	return (count);
}
