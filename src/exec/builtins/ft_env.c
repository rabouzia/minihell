/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:12 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 18:15:46 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	ft_env(t_minishell *minishell, char **arg)
{
	(void)arg;
	minishell->state = 0;
	env_print(minishell->env);
	return (minishell->state);
}

void	env_print(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
