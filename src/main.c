/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:24 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/29 18:04:52 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell minishell;

	(void)ac;
	(void)av;
	(void)env;

	minishell = (t_minishell){0};
	while (1)
	{
		input = readline("🔥$> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		else
			add_history(input);
		if (!parsing(input, &minishell))
			continue ;
		print_token(minishell.token);
		// if (!exec(&minishell))
			// continue ;
		ft_tokenclear(minishell.token);
		minishell.token = 0;
	}
	return (0);
}