/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 15:32:58 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	exec(t_minishell *minishell)
{
	// int 	status[2];
	// pid_t pid;
	if (!builtins(minishell, minishell->command->arguments))
		return (0);
	// while (1)
	// {
	// 	if (pipe(&pid) == -1)
	// 		return (1);
	// 	pid = fork();
	// 	if (pid == -1)
	// 		close_pipe();
	// 	if (pid == 0)
	// 		ft_pipe();
	// 	// if (!redir())
	// 	// 	return (0);
	// 	// if (!bin_cmd())
	// 	// 	return (0);
	// 	arg = arg->next;
	// }
	// waitpid(pid, &status, 0);
	return (1);
}
