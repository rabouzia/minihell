/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:16 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 13:56:47 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_end(t_minishell *minishell)
{
	ft_tokenclear(&minishell->token);
	ft_commandclear(&minishell->command);
	ft_envclear(&minishell->env);
	if (minishell->envp != NULL)
	{
		free_tab(minishell->envp);
		minishell->envp = NULL;
	}
}

void	exit_value(t_minishell *minishell, char *msg)
{
	printf("minihell: exit: %s: numeric argument required\n", msg);
	ft_end(minishell);
	exit(2);
}

int	ft_exit(t_minishell *minishell, char **arg)
{
	char	*str;
	int		ex;

	printf("exit\n");
	if (!arg[1])
	{
		ft_end(minishell);
		exit(0);
	}
	str = arg[1];
	while (*str)
	{
		if (!ft_isnum(*str))
			exit_value(minishell, arg[1]);
		if (ft_isnum(*str) && !arg[2])
		{
			ex = ft_atoi(arg[1]);
			ft_end(minishell);
			exit(ex % 256);
		}
		str++;
	}
	if (arg[2])
		return (printf("minihell: exit: too many arguments\n"), 0);
	return (1);
}
