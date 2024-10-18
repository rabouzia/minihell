/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:16 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 21:13:25 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	exit_value(t_minishell *minishell, char *msg)
{
	minishell->state = 2;
	printf("minihell: exit: %s: numeric argument required\n", msg);
	ft_end(minishell);
	exit(minishell->state);
}

int	too_many(t_minishell *minishell)
{
	printf("minihell: exit: too many arguments\n");
	minishell->state = 1;
	return (1);
}

bool	is_valid_exit(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isnum(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	return (!str[i]);
}

void	while_exit(char *str, char **arg, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!is_valid_exit(str))
		exit_value(minishell, str);
	while (ft_isnum(str[i]) && !arg[2])
	{
		minishell->state = ft_atoi(str);
		if (minishell->state == 0)
			exit_value(minishell, str);
		ft_end(minishell);
		exit(minishell->state % 256);
	}
	i++;
}

int	ft_exit(t_minishell *minishell, char **arg)
{
	int	i;

	i = -1;
	minishell->state = 0;
	printf("exit\n");
	if (!arg[1])
	{
		ft_end(minishell);
		exit(minishell->state);
	}
	while_exit(arg[1], arg, minishell);
	if (arg[2])
		return (too_many(minishell));
	return (minishell->state);
}
