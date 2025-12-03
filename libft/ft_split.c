/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:48:42 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/03 13:14:46 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static int is_delim(char ch, char c)
{
    return (ch == c || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\v' || ch == '\f');
}

static char *get_next_word(char const **s, char c)
{
    const char  *start;
    size_t      len;

    while (is_delim(**s, c))
        (*s)++;

    start = *s;

    while (**s && !is_delim(**s, c))
        (*s)++;

    len = *s - start;

    return ft_substr(start, 0, len);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = get_next_word(&s, c);
		if (!result[i])
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
