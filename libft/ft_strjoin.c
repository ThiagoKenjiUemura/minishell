/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:41:11 by liferrei          #+#    #+#             */
/*   Updated: 2025/08/08 10:22:07 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str3;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str3 = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!str3)
		return (NULL);
	ft_memcpy(str3, s1, s1_len);
	ft_memcpy(str3 + s1_len, s2, s2_len);
	return (str3);
}
