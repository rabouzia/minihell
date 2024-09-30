/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:49:54 by rabouzia          #+#    #+#             */
/*   Updated: 2024/09/30 19:25:53 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '=')
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = 0;
	return (key);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	value = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
	if (!value)
		return (NULL);
	j = 0;
	while (str[i])
		value[j++] = str[i++];
	value[j] = 0;
	return (value);
}
