/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/13 22:52:06 by rabouzia         ###   ########.fr       */
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

void	open_redirections(t_command *cmd, t_minishell *minishell)
{
	t_redir	*redir = cmd->redir;
	
	while (redir != NULL)
	{
		if (redir->type == HEREDOC)
			{ /* open heredoc */ }
		else if (redir->type == IN)
			{ /* open input */ }
		else
			{ /* open output */ }
		redir = redir->next;
	}
	return (EXIT_SUCCESS)
}

int	all_cmd(t_minishell *minishell, int save[2], t_command *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (close(fd[0]), close(fd[1]), -1);
	if (cmd->pid == 0)
	{
		if (cmd->next)
			dup2(fd[1], STDOUT_FILENO);
		(close(save[0]), close(save[1]));
		(close(fd[0]), close(fd[1]));
		open_redirections(cmd);
		if (is_a_builtin(cmd->arguments) == true)
			exit(builtins(minishell, cmd->arguments));
		ft_tabupdate(minishell);
		excute(cmd->arguments, minishell->envp, minishell);
	}
	dup2(fd[0], STDIN_FILENO);
	(close(fd[0]), close(fd[1]));
	return (1);
}

bool	exec(t_command *cmd, t_minishell *minishell)
{
	int save[2];

	save[STDIN_FILENO] = dup(STDIN_FILENO);
	save[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (!cmd->next && is_a_builtin(cmd->arguments))
		return (builtins(minishell, cmd->arguments), 1);
	while (cmd)
	{
		all_cmd(minishell, save, cmd);
		cmd = cmd->next;
	}
	cmd = minishell->command;
	while (cmd)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	dup2(save[STDIN_FILENO], STDIN_FILENO);
	dup2(save[STDOUT_FILENO], STDOUT_FILENO);
	(close(save[0]), close(save[1]));
	return (0);
}