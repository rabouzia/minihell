/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:39:47 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 13:52:23 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	ft_cd(t_minishell *minishell, char **arg)
{
	(void)minishell;
	if (!arg[1])
		return (chdir("/home"), 0);
	if (arg[2])
		return (ft_putstr_fd("minihell: cd: too many arguments\n", 2), 1);
	if (chdir(arg[1]) == -1)
	{
		printf("minishell: cd: %s : No such file or directory\n", arg[1]);
		return (1);
	}
	return (0);
}
