/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:55:12 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/25 23:03:44 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_number_len(unsigned int number)
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

static void	*ft_num_char(char *s, int sign, unsigned int num, size_t len)
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

char	*garbage_itoa(t_shell *data, int n)
{
	unsigned int	number;
	int				sign;
	size_t			number_len;
	char			*number_char;

	sign = 0;
	if (n < 0)
	{
		number = (unsigned int)-n;
		sign = 1;
	}
	else
		number = (unsigned int)n;
	number_len = ft_number_len(number);
	number_char = garbage_calloc(data, (number_len + sign + 1) * sizeof(char));
	if (!number_char)
		return (NULL);
	ft_num_char(number_char, sign, number, number_len);
	return (number_char);
}
