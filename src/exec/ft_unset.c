/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:27 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 19:09:03 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	ft_unset(t_minishell *minishell, char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
		return (0);
	while (arg[i])
	{
		if (!delete_node(&minishell->env, arg[i]))
			i++;
		i++;
	}
	return (1);
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
void	remove_first(t_env **env)
{
	t_env	*second;
	t_env	*cur;
	t_env	*tmp;

	cur = *env;
	second = (*env)->next;
	tmp = (*env);
	env = &second;
	free_node(tmp);
	return ;
}

void	free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
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
	tmp = (cur)->next;
	free_node(cur);
	return ;
}
