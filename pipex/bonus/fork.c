/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:55:46 by rabouzia          #+#    #+#             */
/*   Updated: 2024/04/09 17:03:16 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wait_for_child(pid_t pid, t_pipe *pipex)
{
	int		status[2];
	pid_t	r_waitpid;

	while (1)
	{
		r_waitpid = waitpid(-1, &status[0], 0);
		if (r_waitpid == -1)
			break ;
		if (r_waitpid == pid)
			status[1] = status[0];
	}
	if (pipex->flag == 1)
		unlink(pipex->av[1]);
	if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));
	else if (WIFSIGNALED(status[1]))
		return (WTERMSIG(status[1]) + 128);
	return (0);
}

static void	child_n1(t_pipe *pipex)
{
	close(pipex->pipe[0]);
	pipex->fd_in = open(pipex->av[1], O_RDONLY);
	if (pipex->fd_in == -1)
	{
		perror(pipex->av[1]);
		close(pipex->pipe[1]);
		exit(1);
	}
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
	{
		perror("child_loop:dup2(fd_in)");
		close(pipex->fd_in);
		exit(EXIT_FAILURE);
	}
	close(pipex->fd_in);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
	{
		perror("child_loop:dup2(pipe_fd[1])");
		close(pipex->pipe[1]);
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe[1]);
	excute(cmd_get(pipex->av[2 + pipex->flag]), pipex->env);
}

void	child_n2(t_pipe *p)
{
	close(p->pipe[1]);
	p->fd_out = open(p->av[p->ac - 1], flag_out(p), 0644);
	if (p->fd_out == -1)
	{
		perror(p->av[1]);
		close(p->pipe[0]);
		exit(EXIT_FAILURE);
	}
	if (dup2(p->fd_out, STDOUT_FILENO) == -1)
	{
		perror("child_out:dup2(p->fd_out)");
		close(p->fd_out);
		exit(EXIT_FAILURE);
	}
	close(p->fd_out);
	if (dup2(p->pipe[0], STDIN_FILENO) == -1)
	{
		perror("child_out:dup2(p->pipe[0])");
		close(p->pipe[0]);
		exit(EXIT_FAILURE);
	}
	close(p->pipe[0]);
	excute(cmd_get(p->av[p->ac - 2]), p->env);
}

int	foruku(t_pipe *p)
{
	pid_t	pid;

	if (pipe(p->pipe) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (close(p->pipe[0]), close(p->pipe[1]), -1);
	if (pid == 0)
		child_n1(p);
	close(p->pipe[1]);
	if (p->ac > 6 && ac_loop(p) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(p->pipe[0]), -1);
	if (pid == 0)
		child_n2(p);
	return (close(p->pipe[0]), wait_for_child(pid, p));
}
