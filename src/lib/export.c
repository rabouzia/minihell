/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:48:29 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 19:09:08 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	search_env(t_env *env, char *key)
{
	int	i;

	i = 1;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (i);
		env = env->next;
		i++;
	}
	return (0);
}

void	export_print(t_env *env)
{
	while (env)
	{
		if (!env->value)
			printf("export %s\n", env->key);
		else
			printf("export %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	modify_value(t_env *env, char *key, char *value)
{
	while (ft_strcmp(env->key, key) != 0)
		env = env->next;
	env->value = value;
}
