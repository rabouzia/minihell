/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:09:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 17:44:18 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	change_quote(char quote, int i)
{
	if (quote == '\'' && i == 0)
		return (1);
	else if (quote == '"' && i == 0)
		return (2);
	else
		return (0);
}

int	get_value_len(char *key, t_env *env)
{
	if (!key)
		return (0);
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (ft_strlen(env->value));
		env = env->next;
	}
	return (0);
}

char	*get_value_env(char *key, t_env *env)
{
	if (!key)
		return (0);
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_env_size(char *str, int *i, t_minishell *minishell)
{
	char	c;
	int		start;
	int		len;
	char	*ibaby;

	if (str[*i + 1] == '?')
	{
		ibaby = ft_itoa(minishell->state);
		len = ft_strlen(ibaby);
		(*i) += 2;
		return (free(ibaby), len);
	}
	if (!is_env_valid(str[(*i) + 1], 1))
		return ((*i)++, 1);
	start = ++(*i);
	while (is_env_valid(str[*i], 0))
	{
		(*i)++;
	}
	c = str[*i];
	str[*i] = 0;
	len = get_value_len(str + start, minishell->env);
	str[*i] = c;
	return (len);
}

int	get_expanded_len(char *str, t_minishell *minishell)
{
	int	len;
	int	i;
	int	quote_index;

	len = 0;
	i = 0;
	quote_index = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote_index != 2)
			quote_index = change_quote(str[i++], quote_index);
		else if (str[i] == '"' && quote_index != 1)
			quote_index = change_quote(str[i++], quote_index);
		else
		{
			if (str[i] == '$' && quote_index != 1)
				len += get_env_size(str, &i, minishell);
			else
			{
				i++;
				len++;
			}
		}
	}
	return (len);
}
