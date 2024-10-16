/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:32:39 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 19:16:38 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_envaddback(t_env **head, t_env *new)
{
	if (!head)
		return ;
	if (*head)
		ft_envlast(*head)->next = new;
	else
		*head = new;
}

t_env	*ft_envnew(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

t_env	*ft_envlast(t_env *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_envclear(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free((*env));
		(*env) = tmp;
	}
}

bool	init_env(char **env, t_minishell *minishell)
{
	int		i;
	t_env	*env_t;

	i = 0;
	while (env[i])
	{
		env_t = ft_envnew(get_key(env[i]), get_value(env[i]));
		if (!env_t)
			return (ft_envclear(&minishell->env), 0);
		ft_envaddback(&(minishell->env), env_t);
		i++;
	}
	return (1);
}
