/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:38:26 by rabouzia          #+#    #+#             */
/*   Updated: 2024/07/12 09:51:29 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed
// echo $?
// echo env expansion $USER
int	good_flag(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static bool	handle_flags(const char **args, int *i)
{
	bool	new_line;

	if (!args || !*args)
		return (write(1, "\n", 1), FAILURE);
	*i = 1;
	new_line = 0;
	while (args[*i] && good_flag(args[*i]))
	{
		new_line = true;
		(*i)++;
	}
	return (new_line);
}

static int	print_args(const char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd((char *)args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	return (0);
}

int	ft_echo(const char *cmd, const char **args, t_env *list)
{
	int		i;
	bool	new_line;

	(void)cmd;
	(void)list;
	if (!args || !*args)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i = 1;
	new_line = handle_flags(args, &i);
	print_args(args, i);
	if (!new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}

// void print_echo(t_cmd_list *list)
// {
//     if (ft_echo(list->cmd))
//     {
//         ft_putstr_fd("\n", stdout);
//         ft_putstr_fd(list->cmd->next, stdout);
//     }
//     else
//     {
//         ft_putstr_fd("\n", stdout);
//         ft_putstr_fd(list->cmd->next, stdout);
//         ft_putstr_fd("\n", stdout);
//     }
// }
