/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:19:00 by junsan            #+#    #+#             */
/*   Updated: 2024/07/15 15:51:57 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_arg(const char arg)
{
	if (ft_isalpha(arg) || arg == '_')
		return (0);
	else
		return (1);
}

bool	change_var_if_exist(const char *name, const char *content, t_env *lst)
{
	while (lst)
	{
		if (ft_strncmp(name, lst->name, ft_strlen(name)) == 0)
		{
			free((char *)name);
			if (lst->content)
				free(lst->content);
			if (content)
				lst->content = (char *)content;
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

t_env	*find_next_lower(t_env *lst, char *prec)
{
	t_env	*cur;
	t_env	*next_lower;

	cur = lst;
	next_lower = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->name, prec) > 0 && (next_lower == NULL || \
			ft_strcmp(cur->name, next_lower->name) < 0))
			next_lower = cur;
		cur = cur->next;
	}
	return (next_lower);
}

t_env	*find_lowest(t_env *lst)
{
	t_env	*cur;
	t_env	*lowest;

	cur = lst;
	lowest = cur;
	while (cur)
	{
		if (ft_strcmp(cur->name, lowest->name) < 0)
			lowest = cur;
		cur = cur->next;
	}
	return (lowest);
}
