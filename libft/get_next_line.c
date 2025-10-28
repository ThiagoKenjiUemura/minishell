/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:36:08 by liferrei          #+#    #+#             */
/*   Updated: 2025/09/09 16:59:37 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_and_fill(int fd, char *chunk, char *remainder)
{
	int		bytes_read;
	char	*old_remainder;

	if (!remainder)
		remainder = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(remainder);
			return (NULL);
		}
		chunk[bytes_read] = '\0';
		old_remainder = remainder;
		remainder = ft_strjoin(remainder, chunk);
		free(old_remainder);
	}
	return (remainder);
}

static char	*ft_extract_line(char *remainder)
{
	int		i;
	char	*line;

	if (!remainder || !remainder[0])
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		line = ft_substr(remainder, 0, i + 1);
	else
		line = ft_substr(remainder, 0, i);
	return (line);
}

static char	*ft_update_stash(char *remainder)
{
	int		i;
	char	*new_remainder;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_substr(remainder, i + 1, ft_strlen(remainder) - i);
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	char		*chunk;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	chunk = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!chunk)
		return (NULL);
	remainder[fd] = ft_read_and_fill(fd, chunk, remainder[fd]);
	free(chunk);
	if (!remainder[fd])
		return (NULL);
	line = ft_extract_line(remainder[fd]);
	remainder[fd] = ft_update_stash(remainder[fd]);
	return (line);
}
