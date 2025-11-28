/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:42:15 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/28 15:45:10 by tkenji-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_new_token(t_shell *data, t_token **head, char *value,
			t_type type)
{
	t_token	*new_node;

	new_node = create_token(data, value, type);
	if (!new_node)
		return (-1);
	token_add_back(head, new_node);
	return (0);
}

int	process_one_token(t_shell *data, t_token **head, char *input, int i)
{
	int		len;
	t_type	type;
	char	*value;
	int		next_i;
	t_token	*last;

	len = get_token_len(input, i);
	if (len == -1)
		return (-1);
	type = get_token_type(input, i);
	value = ft_substr(input, i, len);
	if (!value)
		return (-1);
	if (garbage_add(data, value) == 1)
		return (-1);
	next_i = i + len;
	last = get_last_token_local(*head);
	if (last && last->type == WORD && type == WORD && i > 0
		&& input[i - 1] != ' ')
		return (concat_tokens_no_space(data, last, value, next_i));
	if (create_new_token(data, head, value, type) == -1)
		return (-1);
	return (next_i);
}

t_token	*lexer(t_shell *data, char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		i = skip_spaces(input, i);
		if (input[i] == '\0')
			break ;
		i = process_one_token(data, &head, input, i);
		if (i == -1)
			return (NULL);
	}
	return (head);
}
