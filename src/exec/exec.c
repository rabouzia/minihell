/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/17 18:56:50 by rabouzia         ###   ########.fr       */
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

void	set_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
}

int	all_cmd(t_minishell *minishell, int save[2], t_command *cmd)
{
	int	fd[2];
	int	status;

	if (pipe(fd) == -1)
		return (1);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (close(fd[0]), close(fd[1]), -1);
	if (cmd->pid == 0)
	{
		set_signal_child();
		if (cmd->next)
			dup2(fd[1], STDOUT_FILENO);
		(close(save[0]), close(save[1]));
		(close(fd[0]), close(fd[1]));
		open_redirections(cmd, minishell);
		if (cmd->arguments == NULL)
		{
			ft_end(minishell);
			exit(EXIT_SUCCESS);
		}
		if (is_a_builtin(cmd->arguments) == true)
		{
			status = builtins(minishell, cmd);
			ft_end(minishell);
			exit(status);
		}
		ft_tabupdate(minishell);
		excute(cmd->arguments, minishell->envp, minishell);
	}
	dup2(fd[0], STDIN_FILENO);
	(close(fd[0]), close(fd[1]));
	return (1);
}
int	wait_for_child(t_minishell *minishell)
{
	int		status[2];
	pid_t	r_waitpid;

	while (1)
	{
		r_waitpid = waitpid(-1, &status[0], 0);
		if (r_waitpid == -1)
			break ;
		if (r_waitpid == minishell->command->pid)
			status[1] = status[0];
	}
	if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));
	else if (WIFSIGNALED(status[1]))
		return (WTERMSIG(status[1]) + 128);
	return (0);
}

bool	exec(t_command *cmd, t_minishell *minishell)
{
	int	save[2];

	signal(SIGINT, SIG_IGN);
	if (!cmd->next && is_a_builtin(cmd->arguments))
		return (builtins(minishell, cmd), 1);
	save[STDIN_FILENO] = dup(STDIN_FILENO);
	save[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while (cmd)
	{
		all_cmd(minishell, save, cmd);
		cmd = cmd->next;
	}
	cmd = minishell->command;
	free_all_heredoc(minishell->command);
	while (cmd)
	{
		waitpid(cmd->pid, &minishell->state, 0);
		if (WIFEXITED(minishell->state))
			minishell->state = WEXITSTATUS(minishell->state);
		else if (WIFSIGNALED(minishell->state))
			minishell->state = 128 + WTERMSIG(minishell->state);
		else if (WIFSTOPPED(minishell->state))
			minishell->state = 128 + WSTOPSIG(minishell->state);
		cmd = cmd->next;
	}
	dup2(save[STDIN_FILENO], STDIN_FILENO);
	dup2(save[STDOUT_FILENO], STDOUT_FILENO);
	(close(save[0]), close(save[1]));
	return (0);
}
