/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:45:21 by ramzerk           #+#    #+#             */
/*   Updated: 2024/04/09 17:02:50 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(t_pipe *p)
{
	int		fd;
	char	*tmp;

	fd = open(p->av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(p->av[1]);
		exit(1);
	}
	tmp = ft_strjoin(p->av[2], "\n");
	if (!tmp)
	{
		perror("here_doc:ft_strjoin:tmp");
		close(fd);
		exit(1);
	}
	loop_here_doc(tmp, p, fd);
	return (free(tmp), close(fd), 1);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;

	pipex.av = av;
	pipex.env = env;
	pipex.ac = ac;
	pipex.flag = 0;
	if ((pipex.ac < 5) || (ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6))
		return (1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		pipex.flag = here_doc(&pipex);
	return (foruku(&pipex));
}
