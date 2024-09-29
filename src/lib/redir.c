/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:56:35 by rabouzia          #+#    #+#             */
/*   Updated: 2024/09/29 21:57:39 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_rediraddback(t_redir **head, t_redir *new)
{
	if (!head)
		return ;
	if (*head)
		ft_redirlast(*head)->next = new;
	else
		*head = new;
}

t_redir	*ft_redirnew(char *str, t_redir_type type)
{
	t_redir	*redir;

	if (!str)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = str;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

t_redir	*ft_redirlast(t_redir *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_redirclear(t_redir *redir)
{
	t_redir *tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}