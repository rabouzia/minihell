/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:37:51 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 16:30:59 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// printf("\n");
		rl_done = 1;
		g_signal = sig + 128;
		// rl_redisplay();
	}
}

// void	ft_signal_heredoc(int sig)
// {
// 	t_minishell	*mini;

// 	if (sig == SIGINT)
// 	{
// 	---- truc a faire
// 		close(3);
// 		exit(92);
// 	}
// }

void	ft_signal(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}