/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:32:58 by junsan            #+#    #+#             */
/*   Updated: 2024/07/15 15:26:05 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*builtin_new_node(char *name, char *content)
{
	t_env	*res;

	res = (t_env *)malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->name = name;
	res->content = NULL;
	if (content)
		res->content = content;
	res->next = NULL;
	return (res);
}

void	add_builtin_node(t_env **head, char *name, char *content)
{
	t_env	*new_node;
	t_env	*cur;

	new_node = builtin_new_node(name, content);
	if (!name || !new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
}
