/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:08 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 13:50:50 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	good_flag(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || !str[1])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_minishell *minishell, char **arg)
{
	int	flag;
	int	i;

	(void)minishell;
	flag = 0;
	i = 1;
	if (!arg[1])
		return (printf("\n"), 0);
	flag = good_flag(arg[1]);
	if (flag == 1)
		i++;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (1);
}
