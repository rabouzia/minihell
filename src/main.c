/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:24 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/05 17:48:45 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av, char **env)
{
	char		*input;

	(void)ac;
	(void)av;
	(void)env;

	while (1)
	{
		input = readline("minihell$> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		else
			add_history(input);
	}
	return (0);
}