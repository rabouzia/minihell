/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:24 by ramzerk           #+#    #+#             */
/*   Updated: 2024/10/17 19:04:31 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;

	if (!isatty(0))
		return (printf("tty required!!\n"), 1);
	free(((void)ac, (void)av, NULL));
	minishell = (t_minishell){0};
	if (!init_env(env, &minishell))
		return (1);
	minishell.state = 0;
	while (1)
	{
		ft_signal();
		minishell.token = NULL;
		if (minishell.state == 130)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			printf("\n");
		}
		input = readline("🔥$> ");
		if (g_signal != 0)
		{
			minishell.state = g_signal;
			g_signal = 0;
			continue ;
		}
		if (!input)
			break ;
		if (!*input)
			continue ;
		else
			add_history(input);
		if (!parsing(input, &minishell))
			continue ;
		exec(minishell.command, &minishell);
		(ft_tokenclear(&minishell.token), ft_commandclear(&minishell.command));
		free((minishell.token = 0, minishell.command = 0, NULL));
	}
	return (ft_envclear(&minishell.env), 0);
}

// exit code des builtins -> return le state dans tte les builtins

/* 

5."exit -10 ca marche pas"*/