/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:10:41 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/12 18:29:38 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	printf("ARGUMENTS = ");
	while (tab[i])
	{
		printf("%s, ", tab[i]);
		i++;
	}
	// printf("\n");
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**add_argument(char **tab, char *str)
{
	char	**res;
	int		i;

	if (!str)
		return (free_tab(tab), NULL);
	if (!tab)
	{
		res = malloc(sizeof(char *) * 2);
		if (!res)
			return (0);
		res[0] = str;
		res[1] = 0;
		return (res);
	}
	i = 0;
	res = malloc(sizeof(char *) * (tab_len(tab) + 2));
	if (!res)
		return (NULL);
	while (tab[i])
	{
		res[i] = tab[i];
		i++;
	}
	res[i] = str;
	res[++i] = 0;
	return (free(tab), res);
}
