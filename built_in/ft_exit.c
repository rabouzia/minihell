/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:05:58 by rabouzia          #+#    #+#             */
/*   Updated: 2024/07/12 10:04:08 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_exit_args(const char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(\
			args[1][i]) && args[1][i] != '-' && args[1][i] != '+')
		{
			ft_putstr_fd("kashell$> exit: ", STDERR_FILENO);
			ft_putstr_fd((char *)args[0], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (255);
		}
		i++;
	}
	return (0);
}

int	ft_exit(const char *cmd, const char **args, t_env *list)
{
	int	num_args;
	int	exit_code;

	(void)cmd;
	(void)list;
	num_args = 0;
	while (args[num_args])
		num_args++;
	if (num_args == 1)
		(ft_putstr_fd("exit\n", 2), exit(EXIT_SUCCESS));
	if (num_args > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (args[1])
	{
		exit_code = validate_exit_args(args);
		if (exit_code != 0)
			exit(exit_code);
		exit(ft_atoi(args[0]));
	}
	exit(EXIT_SUCCESS);
}
