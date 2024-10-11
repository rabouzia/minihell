/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:14:20 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/11 19:15:45 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static int	word_count(char const *s, char c)
{
	int	count;
	int	on_word;

	count = 0;
	on_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (on_word)
			{
				count++;
				on_word = 0;
			}
		}
		else
			on_word = 1;
		s++;
	}
	return (count + on_word);
}

// static void	*free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (tab)
// 	{
// 		while (tab[i])
// 		{
// 			free(tab[i]);
// 			i++;
// 		}
// 		free(tab);
// 	}
// 	return (NULL);
// }

static char	*copy_next_word(char const *s, char c, int *i)
{
	char	*word;
	int		tmp;
	int		j;

	while (s[*i] && s[*i] == c)
		(*i)++;
	tmp = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	word = malloc((*i - tmp + 1) * sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < *i - tmp)
	{
		word[j] = s[tmp + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		word;
	int		i;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	split = malloc((words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	word = 0;
	while (word < words)
	{
		split[word] = copy_next_word(s, c, &i);
		if (!split[word])
			return (free_tab(split), NULL);
		word++;
	}
	split[words] = NULL;
	return (split);
}

int	pipe_counter(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->redir->type == PIPE)
			i++;
		cmd = cmd->next;
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tmp;
	char	*og_tmp;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	tmp = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (tmp == NULL)
		return (NULL);
	og_tmp = tmp;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (og_tmp);
}

char	*cmd_finder(char **cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*result;
	char	*slash;

	result = NULL;
	slash = ft_strjoin("/", cmd[0]);
	if (!slash)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(env[i], slash);
		if (!tmp)
			return (free(slash), NULL);
		if (access(tmp, F_OK) == 0)
		{
			result = ft_strdup(tmp);
			if (!result)
				return (free(tmp), NULL);
		}
		free(tmp);
		i++;
	}
	return (free_split(env), free(slash), result);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}

void	error_msg(char *path, char **cmd)
{
	if (!path && ft_strchr(cmd[0], '/') != 0)
		ft_putstr_fd("No such file or directory : ", 2);
	else if (!path)
		ft_putstr_fd("command not found: ", 2);
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		ft_putstr_fd("Permission denied: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free_split(cmd);
		free(path);
		exit(126);
	}
	if (path)
		free(path);
	ft_putendl_fd(cmd[0], 2);
	free_split(cmd);
	exit(127);
}
void	excute(char **cmd, char **env, t_minishell *minishell)
{
	int		i;
	char	*path;
	char	**tmp_path;

	tmp_path = NULL;
	path = NULL;
	i = 0;
	if (access(cmd[0], F_OK) == 0)
		path = ft_strdup(cmd[0]);
	else if (env[i])
	{
		while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
			i++;
		if (env[i])
			tmp_path = ft_split(&env[i][5], ':');
		if (!tmp_path)
			error_msg(path, cmd);
		path = cmd_finder(cmd, tmp_path);
	}
	if (!path)
		error_msg(path, cmd);
	execve(path, cmd, env);
	ft_end(minishell);
	error_msg(path, cmd);
}

// int		nb_pipe;
// nb_pipe = pipe_counter(minishell->command);
bool	exec(t_minishell *minishell)
{
	int		fd[2];
	int			save[2];
	t_command	*cmd;

	save[STDIN_FILENO] = dup(STDIN_FILENO);
	save[STDOUT_FILENO] = dup(STDOUT_FILENO);
	cmd = minishell->command;
	if (cmd->next == NULL && is_a_builtin(cmd->arguments) == true)
	{
		builtins(minishell, cmd->arguments);
		return 1;
	}
	while (cmd->next)
	{
		if (pipe(fd) == -1)
			return (1);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (close(fd[0]), close(fd[1]), -1);
		if (cmd->pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			(close(save[0]), close(save[1]));
			(close(fd[0]), close(fd[1]));
			if (is_a_builtin(cmd->arguments) == true)
				exit(builtins(minishell, cmd->arguments));
			excute (cmd->arguments, minishell->pipe.envp, minishell);
		}
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		cmd = cmd->next;
	}
	if (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (-1);
		if (cmd->pid == 0)
		{
			(close(save[0]), close(save[1]));
			if (is_a_builtin(cmd->arguments) == true)
				exit(builtins(minishell, cmd->arguments));
			excute (cmd->arguments, minishell->pipe.envp, minishell);
		}		
	}
	cmd = minishell->command;
	while (cmd)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	dup2(save[STDIN_FILENO],STDIN_FILENO);
	dup2(save[STDOUT_FILENO],STDOUT_FILENO);
	(close(save[0]), close(save[1]));
	return (0);
}

// jouvre les pipes