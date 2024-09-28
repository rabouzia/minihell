/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:54:55 by rabouzia          #+#    #+#             */
/*   Updated: 2024/09/28 20:33:48 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool syntax_analysis(t_minishell *minishell)
{
	return (init_state(minishell->token));	
}

bool init_state(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == WORD)
		return(word_state(token->next));
	if (token->type == REDIR)
		return(redir_state(token->next));
	return (0);
}

bool word_state(t_token *token)
{
	
}

bool redir_state(t_token *token)
{

}

bool pipe_redir(t_token *token)
{
	
}
