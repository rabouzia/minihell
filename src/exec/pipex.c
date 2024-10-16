/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:04:40 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/16 19:09:27 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	*cmd_finder(char **cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*result;
	char	*slash;

	result = NULL;
	if (cmd[0][0] == '\0')
		return (free_tab(env), NULL);
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
				return (free(tmp), free(result), NULL);
		}
		free(tmp);
		i++;
	}
	return (free_tab(env), free(slash), result);
}

void	error_msg(char *path, char **cmd, t_minishell *minishell)
{
	(void)minishell;
	if (!path && ft_strchr(cmd[0], '/') != 0)
		ft_putstr_fd("No such file or directory : ", 2);
	else if (!path)
		ft_putstr_fd("command not found: ", 2);
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		ft_putstr_fd("Permission denied: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free(path);
		ft_end(minishell);
		exit(126);
	}
	if (path)
		free(path);
	ft_putendl_fd(cmd[0], 2);
	ft_end(minishell);
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
	if (!cmd)
		return ;
	if (access(cmd[0], F_OK) == 0)
		path = ft_strdup(cmd[0]);
	else if (env[i])
	{
		while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
			i++;
		if (env[i])
			tmp_path = ft_split(&env[i][5], ':');
		if (!tmp_path)
			error_msg(path, cmd, minishell);
		path = cmd_finder(cmd, tmp_path);
	}
	if (!path)
		error_msg(path, cmd, minishell);
	free_all_heredoc(minishell->command);
	execve(path, cmd, env);
	error_msg(path, cmd, minishell);
	exit(0);
}
