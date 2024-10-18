/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:39:47 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 17:07:48 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	chdir_fail(char *str)
{
	printf("minishell: cd: %s : No such file or directory\n", str);
	return (1);
}

int	ft_cd(t_minishell *minishell, char **arg)
{
	char	*inter;
	char	*home;

	if (!arg[1])
	{
		if (!search_env(minishell->env, "HOME"))
			return (ft_putstr_fd("minihell: cd: HOME not set\n", 2), 1);
		inter = ft_strdup("$HOME");
		home = expand(inter, minishell);
		if (!home)
			return (ft_putstr_fd("minihell: cd: malloc issue\n", 2), 1);
		if (chdir(home) == -1)
		{
			chdir_fail(home);
			return (free(home), free(inter), 1);
		}
		return (free(home), free(inter), 0);
	}
	if (arg[2])
		return (ft_putstr_fd("minihell: cd: too many arguments\n", 2), 1);
	if (chdir(arg[1]) == -1)
		return (chdir_fail(arg[1]));
	return (0);
}
