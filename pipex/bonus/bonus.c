/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:49:08 by ramzerk           #+#    #+#             */
/*   Updated: 2024/04/09 17:02:45 by rabouzia         ###   ########.fr       */
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

int	flag_out(t_pipe *pipex)
{
	if (pipex->flag == 1)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (O_WRONLY | O_CREAT | O_TRUNC);
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

void	loop_here_doc(char *tmp, t_pipe *p, int fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, tmp, ft_strlen(line)) == 0)
		{
			if (!line)
			{
				ft_putstr_fd("\nhere-document delimited ", 2);
				ft_putstr_fd("by end-of-file (wanted `", 2);
				ft_putstr_fd(p->av[2], 2);
				ft_putendl_fd("')", 2);
			}
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}
