/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liferrei <liferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:01:22 by liferrei          #+#    #+#             */
/*   Updated: 2025/11/17 17:02:26 by liferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fake_parser(t_shell *data)
{
    t_cmd *cmd;
    char **tokens;

    if (!data->input || !*data->input)
    {
        data->name_cmd = NULL;
        return ;
    }

    tokens = ft_split(data->input, ' ');
    if (!tokens)
    {
        data->name_cmd = NULL;
        return ;
    }

    cmd = garbage_calloc(data, sizeof(t_cmd));
    if (!cmd)
    {
        data->name_cmd = NULL;
        return ;
    }

    cmd->cmd = tokens[0];
    cmd->args = tokens;
    cmd->is_builtin = is_builtin(cmd->cmd);
    cmd->input_fd = STDIN_FILENO;
    cmd->output_fd = STDOUT_FILENO;
    cmd->next = NULL;

    data->name_cmd = cmd;
}