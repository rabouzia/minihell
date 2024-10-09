/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:27 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/09 18:14:36 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	ft_unset(t_minishell *minishell, char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
		return (1);
	while (arg[i])
	{
		if (!delete_node(&minishell->env, arg[i]))
			i++;
		i++;
	}
	return (1);
}

bool	delete_node(t_env **env, char *to_delete)
{
	int	flag;
	int	len;

	len = count_env(*env);
	flag = search_env(*env, to_delete);
	if (!flag)
		return (0);
	if (flag == 1)
		remove_first(env);
	else if (flag == len + 1)
		remove_last(*env);
	else
		remove_node(*env, to_delete);
	return (1);
}
