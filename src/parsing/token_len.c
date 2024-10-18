/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:55:38 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 16:55:49 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

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
