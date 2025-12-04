/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:43:08 by liferrei          #+#    #+#             */
/*   Updated: 2025/12/04 13:35:29 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_paths_and_return(char **paths, char *return_val)
{
	int	j;

	j = 0;
	if (paths)
	{
		while (paths[j])
			free(paths[j++]);
		free(paths);
	}
	return (return_val);
}

char	*find_in_path(const char *cmd, char **envp)
{
	char	*full;
	char	*path_env;
	char	**paths;
	int		i;

	path_env = env_get(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin3(paths[i], "/", (char *)cmd);
		if (!full)
			return (free_paths_and_return(paths, NULL));
		if (!access(full, X_OK))
			return (free_paths_and_return(paths, full));
		free(full);
		i++;
	}
	return (free_paths_and_return(paths, NULL));
}
