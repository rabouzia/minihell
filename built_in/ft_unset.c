/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:24 by junsan            #+#    #+#             */
/*   Updated: 2024/07/03 09:29:34 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// t_env *del_first(t_env **lst)
// {
//     t_env **tmp;
//     tmp = (*lst)->next;
//     free(*lst);
//     return (tmp);
// }

int	del_node(t_env **lst, const char *to_unset)
{
	t_env	*cur;
	t_env	*prev;

	if (!lst || !*lst)
		return (0);
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		if (strcmp(cur->name, to_unset) == 0)
		{
			if (prev == NULL)
				*lst = cur->next;
			else
				prev->next = cur->next;
			free(cur->name);
			free(cur->content);
			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int	ft_unset(const char *cmd, const char **args, t_env *list)
{
	int	i;

	(void)cmd;
	i = 0;
	if (!args || !list)
		return (FAILURE);
	while (args[i])
	{
		del_node(&list, args[i]);
		i++;
	}
	return (SUCCESS);
}
