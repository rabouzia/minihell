/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:19:11 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 19:25:04 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	remove_first(t_env **env)
{
	t_env	*second;
	t_env	*cur;
	t_env	*tmp;

	cur = *env;
	second = (*env)->next;
	tmp = (*env);
	*env = second;
	free_node(tmp);
	return ;
}

void	remove_last(t_env *env)
{
	t_env	*last;

	last = env;
	while (last->next->next)
		last = last->next;
	env = ft_envlast(env);
	free_node(env);
	last->next = NULL;
}

void	remove_node(t_env *env, char *to_delete)
{
	t_env	*tmp;
	t_env	*cur;

	cur = env;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (ft_strcmp(cur->key, to_delete) == 0)
			break ;
	}
	tmp->next = (cur)->next;
	free_node(cur);
	return ;
}

void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

int	count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->next)
	{
		env = env->next;
		i++;
	}
	return (i);
}
