/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:28:01 by liferrei          #+#    #+#             */
/*   Updated: 2025/08/07 11:41:15 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_print_format(char format, va_list args);
int	ft_print_char(char c);
int	ft_print_str(char *s);
int	ft_print_int(int num);
int	ft_print_uint(unsigned int num);
int	ft_print_hex(unsigned long num, int uppercase);
int	ft_print_ptr(unsigned long ptr);
int	ft_print_percent(void);

#endif