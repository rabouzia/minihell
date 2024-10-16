/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:24 by ramzerk           #+#    #+#             */
/*   Updated: 2024/10/16 14:34:45 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_minishell	minishell;

	free(((void)ac, (void)av, NULL));
	minishell = (t_minishell){0};
	if (!init_env(env, &minishell))
		return (1);
	free((minishell.state = 0, ft_signal(), NULL));
	while (1)
	{
		minishell.token = NULL;
		input = readline("🔥$> ");
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

// heredoc + signaux heredoc
// ouvrir les fd dans les builtins
// exit code des builtins
// ctrl-c dans cat -> double prompt
// echo machin | cat | cat | cat | cat -> leak