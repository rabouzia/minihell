/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:46:32 by rabouzia          #+#    #+#             */
/*   Updated: 2024/09/30 20:10:17 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	add_pipe(int *i, t_minishell *minishell)
{
	t_token	*new;

	new = ft_tokennew(NULL, PIPE);
	if (!new)
		return (0);
	ft_tokenaddback(&(minishell->token), new);
	(*i)++;
	return (1);
}

bool	add_redir_double(char *input, int *i, t_minishell *minishell)
{
	t_token	*new;
	char	*str;

	str = ft_substr(input, *i, 2);
	if (!str)
		return (0);
	new = ft_tokennew(str, REDIR);
	if (!new)
		return (free(str), 0);
	ft_tokenaddback(&(minishell->token), new);
	(*i) += 2;
	return (1);
}

bool	add_redir_simple(char *input, int *i, t_minishell *minishell)
{
	t_token	*new;
	char	*str;

	str = ft_substr(input, *i, 1);
	if (!str)
		return (0);
	new = ft_tokennew(str, REDIR);
	if (!new)
		return (free(str), 0);
	ft_tokenaddback(&(minishell->token), new);
	(*i)++;
	return (1);
}

// if (input[i] == '"' || input[i] == '\'')
// {
// 	quote = input[i];
// 	len++;
// 	while (input[++i] != quote)
// 	{
// 		len++;
// 	}
// 	len++;
// }

int	get_len_word(char *input, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (input[i] && !is_not_word(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			len++;
			while (input[++i] != quote)
			{
				len++;
			}
			len++;
		}
		len++;
		i++;
	}
	return (len);
}

void	add_between_quotes(char *str, char *input, int *j, int *i)
{
	char	quote;

	quote = input[(*i)++];
	str[(*j)++] = quote;
	while (input[*i] != quote)
		str[(*j)++] = input[(*i)++];
	str[(*j)++] = input[(*i)++];
}

bool	add_word(char *input, int *i, t_minishell *minishell)
{
	t_token	*new;
	char	*str;
	int		j;

	str = malloc(sizeof(char) * get_len_word(input, *i) + 1);
	if (!str)
		return (0);
	j = 0;
	while (input[*i] && !is_not_word(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
			add_between_quotes(str, input, &j, i);
		else
			str[j++] = input[(*i)++];
	}
	str[j] = 0;
	new = ft_tokennew(str, WORD);
	if (!new)
		return (free(str), 0);
	ft_tokenaddback(&(minishell->token), new);
	return (1);
}
