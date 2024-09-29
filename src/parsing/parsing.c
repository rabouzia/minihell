/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:11 by rabouzia          #+#    #+#             */
/*   Updated: 2024/09/29 18:29:47 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	check_quotes(char *input)
{
	char	c;
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			c = input[i++];
			while (input[i] && input[i] != c)
				i++;
			if (!input[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int	parsing(char *input, t_minishell *minishell)
{
	if (!check_quotes(input))
		return (dprintf(2, "Error : open quotes\n"), 0);
	if (!tokenization(input, minishell))
		return (0);
	if (!syntax_analysis(minishell))
		return (dprintf(2, "Error : syntax error\n"), 0);
	// if (!tidying(minishell))
	// 	return (0);
	return (1);
}

// ls "-l ls df as"
