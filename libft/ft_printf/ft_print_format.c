/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:32:48 by liferrei          #+#    #+#             */
/*   Updated: 2025/08/09 18:08:01 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(char format, va_list args)
{
	if (format == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (format == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (format == 'u')
		return (ft_print_uint(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_print_hex(va_arg(args, unsigned long), 0));
	else if (format == 'X')
		return (ft_print_hex(va_arg(args, unsigned long), 1));
	else if (format == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long)));
	else if (format == '%')
		return (ft_print_percent());
	return (0);
}
