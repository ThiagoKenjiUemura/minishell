/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiagouemura <thiagouemura@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:39:16 by tkenji-u          #+#    #+#             */
/*   Updated: 2025/11/27 17:32:48 by thiagouemur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator_len(char *input, int i)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (2);
		else
			return (1);
	}
	if (input[i] == '|')
		return (1);
	return (0);
}

int	get_word_len(char *input, int i)
{
	int	start_index;

	start_index = i;
	while (input[i] != '\0' && input[i] != '>' && input[i] != '|'
		&& input[i] != '<' && input[i] != ' '
		&& input[i] != '\'' && input[i] != '\"')
		i++;
	return (i - start_index);
}

int process_one_token(t_shell *data, t_token **head, char *input, int i)
{
	int		len;
	t_type	type;
	char	*value;
	t_token	*new_node;
	t_token	*last;

	new_node = NULL;
	len = get_token_len(input, i);
	type = get_token_type(input, i);
	value = ft_substr(input, i, len);
	if (!value)
		return (-1);
	if (garbage_add(data, value) == 1)
	{
		free(value);
		return (-1);
	}
	/* Se existe token anterior, pega-o */
	last = NULL;
	if (head && *head)
	{
		last = *head;
		while (last->next)
			last = last->next;
	}
	/* Se último token e este são WORDs e NÃO houve espaço entre eles -> concatena */
	if (last && last->type == WORD && type == WORD && i > 0 && input[i - 1] != ' ')
	{
		/* concatena ao valor do token anterior usando garbage (evita leaks) */
		char *joined = garbage_strjoin(data, last->value, value);
		if (!joined)
			return (-1);
		last->value = joined;
		/* cleanup: value já foi "adicionado" ao garbage por garbage_add, não precisa free */
		return (i + len);
	}
	/* Caso normal: criar novo token */
	new_node = create_token(data, value, type);
	if (!new_node)
		return (-1);
	token_add_back(head, new_node);
	return (i + len);
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
