/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:04:40 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/09 12:45:11 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	**cmd_get(char *cmd)
{
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd || !split_cmd[0])
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		free(split_cmd);
		exit(127);
	}
	return (split_cmd);
}

static void	child_loop(t_pipe *pipex)
{
	close(pipex->pipe[0]);
	if (dup2(pipex->oldfd, STDIN_FILENO) == -1)
	{
		perror("child_loop:dup2(pipex->oldfd)");
		close(pipex->oldfd);
		exit(EXIT_FAILURE);
	}
	close(pipex->oldfd);
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
	{
		perror("child_loop:dup2(pipex->pipe[1])");
		close(pipex->pipe[1]);
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe[1]);
	excute(cmd_get(pipex->av[pipex->i]), pipex->env);
}

int	ac_loop(t_pipe *pipex)
{
	pid_t	pid;

	pipex->i = 3;
	while (pipex->ac - 2 > pipex->i)
	{
		pipex->oldfd = pipex->pipe[0];
		if (pipe(pipex->pipe) == -1)
			return (close(pipex->oldfd), -1);
		pid = fork();
		if (pid == -1)
			return (close(pipex->pipe[0]), close(pipex->oldfd),
				close(pipex->pipe[1]), -1);
		if (pid == 0)
			child_loop(pipex);
		close(pipex->pipe[1]);
		close(pipex->oldfd);
		pipex->i++;
	}
	return (0);
}

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


//  | wc -l /std/out

// execve (ls makefile) | 