/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tidying.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:08:53 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/13 17:13:04 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

t_redir_type	find_redir_type(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(str, ">"))
		return (OUT);
	else
		return (IN);
}

bool	handle_token(t_token **token, t_command *cmd, t_minishell *minishell)
{
	t_redir	*redir;

	if ((*token)->type == WORD)
	{
		cmd->arguments = add_argument(cmd->arguments, expand((*token)->str, minishell));
		if (!cmd->arguments)
			return (0);
	}
	else
	{
		redir = ft_redirnew(expand((*token)->next->str, minishell), find_redir_type((*token)->str));
		if (!redir)
			return (0);
		ft_rediraddback(&(cmd->redir), redir);
		(*token) = (*token)->next;
	}
	(*token) = (*token)->next;
	return (1);
}

bool	tidying(t_minishell *minishell)
{
	t_token		*token;
	t_command	*cmd;

	token = minishell->token;
	while (token)
	{
		cmd = ft_commandnew(NULL, NULL);
		if (!cmd)
			return (ft_commandclear(&minishell->command), 0);
		while (token && token->type != PIPE)
		{
			if (!handle_token(&token, cmd, minishell))
			{
				free_tab(cmd->arguments);
				ft_redirclear(cmd->redir);
				return (0);
			}
		}
		ft_commandaddback(&(minishell->command), cmd);
		if (!token)
			break ;
		token = token->next;
	}
	return (1);
}
