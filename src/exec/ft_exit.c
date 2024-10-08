/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:40:16 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 19:32:30 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

/*

-------------------

>exit a d d dd 
exit
bash: exit: a: numeric argument required
>echo $?
2

-------------------
>exit 3 3
exit
bash: exit: too many arguments
>echo $?
1

*/

bool ft_exit(t_minishell *minishell, char **arg)
{
	(void) minishell;
	if (!arg[1])
	{
		printf("exit\n");
		exit(0); // leak
	}
	return 1;
}