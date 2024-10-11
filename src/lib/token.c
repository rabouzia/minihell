/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:10:46 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/11 17:18:52 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_tokenaddback(t_token **head, t_token *new)
{
	if (!head)
		return ;
	if (*head)
		ft_tokenlast(*head)->next = new;
	else
		*head = new;
}

t_token	*ft_tokennew(char *str, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*ft_tokenlast(t_token *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_tokenclear(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->type != PIPE)
			free(token->str);
		free(token);
		token = tmp;
	}
}
