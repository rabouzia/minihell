/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:33:23 by rabouzia          #+#    #+#             */
/*   Updated: 2024/09/29 21:42:11 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	*type_name_token(t_token_type type)
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

char	*type_name_redir(t_redir_type type)
{
	switch (type)
	{
	case IN:
		return ("IN");
	case OUT:
		return ("OUT");
	case HEREDOC:
		return ("HEREDOC");
	case APPEND:
		return ("APPEND");
	}
}

void	print_token(t_token *token)
{
	while (token)
	{
		if (token->type != PIPE)
			printf("	str =  %s\n", token->str);
		printf("	type =  %s\n", type_name_token(token->type));
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

void	print_redir(t_redir *redir)
{
	while (redir)
	{
		printf("file = %s, ", redir->file);
		printf("type =  %s  ", type_name_redir(redir->type));
		if (redir->next)
		{
			printf(" ----> ");
		}
		redir = redir->next;
	}
}

void	print_command(t_command *command)
{
	while (command)
	{
		print_tab(command->arguments);
		print_redir(command->redir);
		if (command->next)
		{
			printf("	\n");
			printf("	|\n");
			printf("	|\n");
			printf("	|\n");
			printf("	V\n");
			printf("	\n");
		}
		command = command->next;
	}
	printf("	\n");
}
