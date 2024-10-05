/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:09:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/05 21:17:27 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int change_quote(char quote, int i)
{
	if (quote == '\'' && i == 0)
		return (1);
	else if (quote == '"' && i == 0)
		return (2);
	else
		return (0);
}

int get_value_len(char *key, t_env *env)
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

char *get_value_env(char *key, t_env *env)
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

int get_env_size(char *str, int *i, t_minishell *minishell)
{
	char c;
	int start;
	int len;
	// if (str[*i + 1] == '?')
	// {
	// 	*i += 2;
	// 	return (ft_strlen(ft_itoa(minishell->state)));
	// }
	printf("la\n");
	if (!is_env_valid(str[*i + 1], 1))
		return ((*i)++, 1);
	start = ++(*i);
	while (is_env_valid(str[*i], 0))
	{
		printf("i : %d\n", *i);
		(*i)++;
	}
	c = str[*i];
	str[*i] = 0;
	printf("value = %s\n", str + start);
	len = get_value_len(str + start, minishell->env);
	str[*i] = c;
	printf("value : %d\n", len);
	return (len);
}

int get_expanded_len(char *str, t_minishell *minishell)
{
	int len;
	int i;
	int quote_index;

	len = 0;
	i = 0;
	quote_index = 0;
	printf("ici get expanded len\n");
	while (str[i])
	{
		printf("ici boucle gel\n");
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

void	get_env_value(char *str, char *expanded, int *i, t_minishell *minishell)
{
	char c;
	char *value;
	int start;
	// if (str[*i + 1] == '?')
	// {
	// 	*i += 2;
	//	ft_strncat(expanded, ft_itoa(minishell->state), ft_strlen(ft_itoa(minishell->state)));
	//	return ;
	// }
	// printf("ici\n");
	if (!is_env_valid(str[*i + 1], 1))
	{
		ft_strncat(expanded, str + (*i)++, 1);
		return ;
	}
	start = ++(*i);
	while (is_env_valid(str[*i], 0))
		(*i)++;
	c = str[*i];
	str[*i] = 0;
	value = get_value_env(str + start, minishell->env);
	ft_strncat(expanded, value, ft_strlen(value));
	str[*i] = c;
	return ;
}

char	*expand(char *str, t_minishell *minishell)
{
	char *expanded;
	int i;
	int quote_index;

	int len = get_expanded_len(str, minishell);
	dprintf(2, "expanded len : %d\n", len);
	expanded = malloc(len + 1);
	if (!expanded)
		return (NULL);
	ft_memset(expanded, 0, len + 1);
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
				get_env_value(str, expanded, &i, minishell);
			else
				ft_strncat(expanded, str + i++, 1);
		}
	}
	return (expanded);
}


//  fsdfd'df  s$sdfsd'"sdf$HOME$USER"vg
//  fsdfddf s$sdfsdsdfpath_to_homerabouziavg