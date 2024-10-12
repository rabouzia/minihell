/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:24 by ramzerk           #+#    #+#             */
/*   Updated: 2024/10/12 12:45:17 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;

	(void)ac;
	(void)av;
	minishell = (t_minishell){0};
	if (!init_env(env, &minishell))
		return (1);
	while (1)
	{
		ft_tokenclear(minishell.token);
		minishell.token = NULL;
		input = readline("🔥$> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		else
			add_history(input);
		// printf("input: %s\n", input);
		if (!parsing(input, &minishell))
			continue ;
		exec(&minishell);
		ft_commandclear(minishell.command);
		minishell.token = 0;
		minishell.command = 0;
	}
	ft_envclear(minishell.env);
	return (0);
}


// update char **env
