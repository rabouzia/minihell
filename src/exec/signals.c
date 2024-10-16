/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:37:51 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 19:08:57 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_done = 1;
		g_signal = sig + 128;
	}
}

void	ft_signal(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
