/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:25:18 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/27 10:29:25 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static int	ft_strlen_safe(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

static int	ft_strcopy(char *dest, const char *src, int start_i)
{
	int	i;

	i = 0;
	if (!src)
		return (start_i);
	while (src[i])
	{
		dest[start_i + i] = src[i];
		i++;
	}
	return (start_i + i);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		len;
	int		i;
	char	*res;

	len = ft_strlen_safe(s1) + ft_strlen_safe(s2) + ft_strlen_safe(s3);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	i = ft_strcopy(res, s1, i);
	i = ft_strcopy(res, s2, i);
	i = ft_strcopy(res, s3, i);
	res[i] = '\0';
	return (res);
}
