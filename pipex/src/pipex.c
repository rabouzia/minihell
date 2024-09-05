/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:45:21 by ramzerk           #+#    #+#             */
/*   Updated: 2024/04/09 16:34:29 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	child0(int fd[2], char **av, char **env)
{
	int	fd_in;

	close(fd[0]);
	fd_in = open(av[1], O_RDONLY, 0644);
	if (fd_in == -1)
	{
		close(fd[1]);
		perror(av[1]);
		exit(1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		exit(EXIT_FAILURE);
	}
	close(fd_in);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	excute(cmd_get(av[2]), env);
}

static void	child1(int fd[2], char **av, char **env)
{
	int	fd_out;

	close(fd[1]);
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		close(fd[0]);
		perror(av[4]);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		exit(EXIT_FAILURE);
	}
	close(fd_out);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	excute(cmd_get(av[3]), env);
}

static int	wait_for_child(pid_t pid)
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
	if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));
	else if (WIFSIGNALED(status[1]))
		return (WTERMSIG(status[1]) + 128);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5 || pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
		child0(pipe_fd, av, env);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
		child1(pipe_fd, av, env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (wait_for_child(pid));
}
