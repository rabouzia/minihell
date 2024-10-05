/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:23 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/06 01:41:22 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool ft_pwd(t_minishell *minishell, char **arg)
{
	(void) minishell;
	(void) arg;
	char *pwd;
	pwd = getcwd(NULL,0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return 1;
}