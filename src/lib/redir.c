/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:56:35 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 19:08:33 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	get_heredoc(t_redir *redir, t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (g_signal != 0)
		{
			free_tab(redir->heredoc_content);
			free(line);
			minishell->state = g_signal;
			g_signal = 0;
			return (EXIT_FAILURE);
		}
		if (!line)
		{
			printf("error message\n");
			break ;
		}
		if (ft_strcmp(line, redir->file) == 0)
			break ;
		redir->heredoc_content = add_argument(redir->heredoc_content,
				expand(line, minishell));
		free(line);
	}
	return (EXIT_SUCCESS);
}

void	ft_rediraddback(t_redir **head, t_redir *new)
{
	if (!head)
		return ;
	if (*head)
		ft_redirlast(*head)->next = new;
	else
		*head = new;
}

t_redir	*ft_redirnew(char *str, t_redir_type type, t_minishell *minishell)
{
	t_redir	*redir;

	if (!str)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = str;
	redir->heredoc_content = NULL;
	redir->type = type;
	if (type == HEREDOC)
	{
		if (get_heredoc(redir, minishell) == EXIT_FAILURE)
		{
			free(redir);
			free(str);
			return (NULL);
		}
	}
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
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}
