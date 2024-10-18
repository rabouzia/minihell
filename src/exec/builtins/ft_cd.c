/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:39:47 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 18:22:14 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	chdir_fail(char *str)
{
	printf("minishell: cd: %s : No such file or directory\n", str);
	return (1);
}

int	ft_cd(t_minishell *shell, char **arg)
{
	char	*inter;
	char	*home;

	shell->state = 1;
	if (!arg[1])
	{
		if (!search_env(shell->env, "HOME"))
			return (printf("minihell: cd: HOME not set\n"), shell->state);
		inter = ft_strdup("$HOME");
		home = expand(inter, shell);
		if (!home)
			return (printf("minihell: cd: malloc issue\n"), shell->state);
		if (chdir(home) == -1)
		{
			chdir_fail(home);
			return (free(home), free(inter), 1);
		}
		return (free(home), free(inter), 0);
	}
	if (arg[2])
		return (printf("minihell: cd: too many arguments\n"), shell->state);
	if (chdir(arg[1]) == -1)
		return (chdir_fail(arg[1]));
	shell->state = 0;
	return (shell->state);
}
