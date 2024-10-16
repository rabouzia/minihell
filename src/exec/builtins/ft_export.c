/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 14:28:56 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	export_rule(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '_' && ft_isalpha(str[0]) != 1)
		return (0);
	while (str[i])
	{
		if (str[i] != '_' && ft_isalpha(str[i]) != 1 && ft_isnum(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_minishell *minishell, char **arg)
{
	int	i;

	if (!arg[1])
	{
		export_print(minishell->env);
		return (1);
	}
	i = 1;
	while (arg[i])
	{
		if (!export_rule(arg[i]))
		{
			printf("bash: export: `%s': not a valid identifier\n", arg[i]);
			i++;
			continue ;
		}
		export_create(minishell, arg[i]);
		i++;
	}
	return (1);
}

void	export_create(t_minishell *minishell, char *arg)
{
	t_env	*new;
	char	*key;
	char	*value;

	if (ft_strchr(arg, '='))
	{
		key = get_key(arg);
		value = get_value(arg);
		new = ft_envnew(key, value);
	}
	else
	{
		if (search_env(minishell->env, arg))
			return ;
		key = ft_strdup(arg);
		new = ft_envnew(key, NULL);
	}
	if (!search_env(minishell->env, key))
		ft_envaddback(&minishell->env, new);
	else
		modify_value(minishell->env, key, value);
}
