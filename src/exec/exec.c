/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/06 01:56:40 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	exec(t_minishell *minishell)
{
	int 	status[2];
	t_command *arg;
	arg = minishell->command;
	pid_t pid;
	while (1)
	{

		if (pipe(pid) == -1)
			return 1;
		pid = fork();
		if (pid == -1)
			close_pipe();
		if (pid == 0)
			ft_pipe();
		// if (!redir())
		// 	return (0);
		if (!builtins(minishell, arg))
			return (0);
		// if (!bin_cmd())
		// 	return (0);
		arg = arg->next;
	}
		waitpid(pid, &status, 0);
	return 1;
}