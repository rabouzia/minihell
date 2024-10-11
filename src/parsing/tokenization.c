/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:22:13 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/11 19:02:15 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	skip_spaces(char *input, int *i)
{
	while (is_space(input[*i]))
		(*i)++;
	return (input[*i] == 0);
}

bool	tokenization(char *input, t_minishell *minishell)
{
	int		i;
	bool	success;

	i = 0;
	while (0 [input + i]) // hihi
	{
		if (skip_spaces(input, &i))
			break ;
		if (input[i] == '|')
			success = add_pipe(&i, minishell);
		else if (!ft_strncmp(input + i, ">>", 2))
			success = add_redir_double(input, &i, minishell);
		else if (!ft_strncmp(input + i, "<<", 2))
			success = add_redir_double(input, &i, minishell);
		else if (!ft_strncmp(input + i, "<", 1))
			success = add_redir_simple(input, &i, minishell);
		else if (!ft_strncmp(input + i, ">", 1))
			success = add_redir_simple(input, &i, minishell);
		else
			success = add_word(input, &i, minishell);
		if (!success)
			return (0);
		// printf("%c", input[i]);
		// print_command(minishell->command);
		// print_token(minishell->token);
		
	}
	return (1);
}
