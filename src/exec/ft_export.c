/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/06 01:47:04 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool ft_export(t_minishell *minishell, char **arg)
{
	(void) minishell;
	(void) arg;
	export_print(minishell->env);
	return 1;
}
void export_print(t_env *env)
{
	while(env)
	{	
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}