/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:04:33 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 17:07:33 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	open_input(t_redir *redir, t_minishell *minishell)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->file);
		ft_end(minishell);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	open_output(t_redir *redir, t_minishell *minishell)
{
	int	fd;

	if (redir->type == OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->type == APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file);
		ft_end(minishell);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	free_all_heredoc(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->redir && cmd->redir->heredoc_content)
			free_tab(cmd->redir->heredoc_content);
		cmd = cmd->next;
	}
}

void	open_heredoc(t_redir *redir, t_minishell *minishell)
{
	int			fd[2];
	int			i;
	t_command	*cmd;

	cmd = minishell->command;
	i = 0;
	(void)minishell;
	if (pipe(fd) == -1)
	{
		printf("pipe error :");
		ft_end(minishell);
		exit(-1);
	}
	while (redir->heredoc_content && redir->heredoc_content[i])
	{
		ft_putendl_fd(redir->heredoc_content[i], fd[1]);
		i++;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	open_redirections(t_command *cmd, t_minishell *minishell)
{
	t_redir	*redir;

	(void)minishell;
	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == HEREDOC)
			open_heredoc(redir, minishell);
		else if (redir->type == IN)
			open_input(redir, minishell);
		else
			open_output(redir, minishell);
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
