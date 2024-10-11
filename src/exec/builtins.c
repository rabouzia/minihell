/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:14:23 by ramzerk           #+#    #+#             */
/*   Updated: 2024/10/11 18:42:46 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	builtins(t_minishell *minishell, char **arg)
{
	if (arg == NULL || arg[0] == NULL)
		return (0);
	if (ft_strncmp("cd", arg[0], 2) == 0)
		return (ft_cd(minishell, arg));
	if (ft_strncmp("echo", arg[0], 4) == 0)
		return (ft_echo(minishell,arg));
	if (ft_strncmp("env", arg[0], 3) == 0)
		return (ft_env(minishell,arg));
	if (ft_strncmp("exit", arg[0], 4) == 0)
		return (ft_exit(minishell,arg));
	if (ft_strncmp("export", arg[0], 6) == 0)
		return (ft_export(minishell,arg));
	if (ft_strncmp("pwd", arg[0], 3) == 0)
		return (ft_pwd(minishell,arg));
	if (ft_strncmp("unset", arg[0], 5) == 0)
		return (ft_unset(minishell,arg));
	else
		return 0;
}

bool	is_a_builtin(char **arg)
{
	if (arg == NULL || arg[0] == NULL)
		return (0);
	if (ft_strncmp("cd", arg[0], 2) == 0)
		return (1);
	if (ft_strncmp("echo", arg[0], 4) == 0)
		return (1);
	if (ft_strncmp("env", arg[0], 3) == 0)
		return (1);
	if (ft_strncmp("exit", arg[0], 4) == 0)
		return (1);
	if (ft_strncmp("export", arg[0], 6) == 0)
		return (1);
	if (ft_strncmp("pwd", arg[0], 3) == 0)
		return (1);
	if (ft_strncmp("unset", arg[0], 5) == 0)
		return (1);
	return 0;
}
