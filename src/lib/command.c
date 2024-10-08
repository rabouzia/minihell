/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:54:04 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 16:33:40 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_commandaddback(t_command **head, t_command *new)
{
	if (!head)
		return ;
	if (*head)
		ft_commandlast(*head)->next = new;
	else
		*head = new;
}

t_command	*ft_commandnew(char **tab, t_redir *redir)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->arguments = tab;
	cmd->redir = redir;
	cmd->next = NULL;
	return (cmd);
}

t_command	*ft_commandlast(t_command *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_commandclear(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_tab(cmd->arguments);
		ft_redirclear(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}
