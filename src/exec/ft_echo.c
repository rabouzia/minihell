/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:08 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/06 10:36:19 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	ft_echo(t_minishell *minishell, char **arg)
{
	(void) minishell;
	(void) arg;
	int i = 1;
	while(arg[i])
	{
		// if (arg[1][0] == '-')
		// 	good_flag(arg[i]);
			
		// else
			printf("%s", arg[i]);
			printf(" ");

		i++;
	}
	return 1;
}

int	good_flag(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}