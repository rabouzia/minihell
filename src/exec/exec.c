/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/04 13:50:40 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	exec(t_minishell *minishell)
{
	char **arg;
	if (!ft_pipe())
		return (0);
	if (fork())
		return (0);
	if (!redir())
		return (0);
	if (!builtins(minishell, arg))
		return (0);
	if (!bin_cmd())
		return (0);
	waitpid(pid, &status, 0);
}

bool	builtins(t_minishell *minishell, char **arg)
{
	if (ft_strncmp("echo", arg[0], 4) == 0)
		return (ft_echo(arg));
	if (ft_strncmp("cd", arg[0], 2) == 0)
		return (ft_cd(arg));
	if (ft_strncmp("pwd", arg[0], 3) == 0)
		return (ft_pwd(arg));
	if (ft_strncmp("export", arg[0], 6) == 0)
		return (ft_export(arg));
	if (ft_strncmp("unset", arg[0], 5) == 0)
		return (ft_unset(arg));
	if (ft_strncmp("env", arg[0], 3) == 0)
		return (ft_env(arg));
	if (ft_strncmp("exit", arg[0], 4) == 0)
		return (ft_exit(arg));
}