/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:41:24 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/22 16:47:31 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*garbage_substr(t_shell *data, char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*sub;

	if (!s)
		return (NULL);

	slen = ft_strlen(s);

	if (start >= slen)
		return (garbage_strdup(data, ""));

	if (len > slen - start)
		len = slen - start;

	sub = garbage_calloc(data, len + 1);
	if (!sub)
		return (NULL);

	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

char	*garbage_strjoin(t_shell *data, char const *s1, char const *s2)
{
	char	*str3;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);

	str3 = garbage_calloc(data, (s1_len + s2_len + 1));
	if (!str3)
		return (NULL);

	ft_memcpy(str3, s1, s1_len);
	ft_memcpy(str3 + s1_len, s2, s2_len);

	return (str3);
}

char	*garbage_strdup(t_shell *data, const char *src)
{
	char	*dup;

	dup = ft_strdup(src);
	if (!dup)
		return (NULL);
	if (garbage_add(data, dup))
	{
		free(dup);
		return (NULL);
	}
	return (dup);
}