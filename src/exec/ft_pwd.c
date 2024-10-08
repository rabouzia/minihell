/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:23 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 17:45:51 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	ft_pwd(t_minishell *minishell, char **arg)
{
	char	*pwd;

	(void)minishell;
	(void)arg;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	return (1);
}
