/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:33:23 by rabouzia          #+#    #+#             */
/*   Updated: 2024/09/29 18:15:07 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char *type_name(t_token_type type)
{
	switch (type)
	{
		case PIPE:
			return ("PIPE");
		case WORD:
			return ("WORD");
		case REDIR:
			return ("REDIR");
	}
}


void	print_token(t_token *token)
{
	while(token)
	{
		printf("	str =  %s\n", token->str);
		printf("	type =  %s\n", type_name(token->type));
		if (token->next)
		{
			printf("	\n");
			printf("	|\n");
			printf("	|\n");
			printf("	|\n");
			printf("	V\n");
			printf("	\n");
		}
		token = token->next;
	}
}


