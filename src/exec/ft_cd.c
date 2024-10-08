/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:39:47 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 15:28:19 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

// bash: cd: too many arguments
// bash: cd: dsf: No such file or directory

bool	ft_cd(t_minishell *minishell, char **arg)
{
	(void)minishell;
	if (!arg[1])
		return (chdir("/home"), 0);
	if (arg[2])
		return (ft_putstr_fd("minihell: cd: too many arguments\n", 2), 0);
	if (chdir(arg[1]) == -1)
	{
		printf("minishell: cd: %s : No such file or directory\n", arg[1]);
		return (0);
	}
	return (1);
}