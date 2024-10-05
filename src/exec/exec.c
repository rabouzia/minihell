/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/06 01:35:39 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	exec(t_minishell *minishell)
{
	
	char **arg;
	arg = minishell->command->arguments;
	// if (!ft_pipe())
	// 	return (0);
	// if (fork())
	// 	return (0);
	// if (!redir())
	// 	return (0);
	if (!builtins(minishell, arg))
		return (0);
	// if (!bin_cmd())
	// 	return (0);
	// waitpid(pid, &status, 0);
	return 1;
}