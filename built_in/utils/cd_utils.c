/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:29:42 by junsan            #+#    #+#             */
/*   Updated: 2024/07/15 22:22:52 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chdir_to_home(t_env *env)
{
	char	*home_path;

	while (env)
	{
		if (ft_strncmp(env->name, "HOME", 4) == 0)
		{
			home_path = env->content;
			break ;
		}
		env = env->next;
	}
	if (chdir(home_path) == -1)
	{
		ft_putstr_fd("cd : HOME not set\n", 2);
		return (FAILURE);
	}
	update_pwd_oldpwd(env, home_path);
	return (SUCCESS);
}

static void	print_no_such_file_or_directory_error(char *arg)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	change_dir(const char *path, t_env *env)
{
	char	*new_pwd;

	if (!path || *path == '\0')
		return (0);
	if (ft_strncmp(path, "-", 1) == 0)
	{
		if (env->old_pwd && env->old_pwd->content)
		{
			if (chdir(env->old_pwd->content) == -1)
				return (0);
			return (swap_pwd_oldpwd(env), 1);
		}
		else
			return (ft_putstr_fd("cd : OLDPWD not set\n", 2), 0);
	}
	if (chdir(path) == -1)
		return (print_no_such_file_or_directory_error((char *)path), 0);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (0);
	update_pwd_oldpwd(env, new_pwd);
	free(new_pwd);
	return (1);
}

// bool	get_cur_dir(void)
// {
// 	char	cwd[MAX_PATH_LENGTH];

// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		printf("%s\n", cwd);
// 		return (SUCCESS);
// 	}
// 	else
// 		perror("getcwd");
// 	return (FAILURE);
// }

// bool	file_exist(const char *filename)
// {
// 	return (access(filename, F_OK) == 0);
// }

// void	list_dir(const char *dirname)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;

// 	dir = opendir(dirname);
// 	if (dir == NULL)
// 	{
// 		perror("opendir");
// 		return ;
// 	}
// 	entry = readdir(dir);
// 	while (entry != NULL)
// 		printf("%s\n", entry->d_name);
// 	closedir(dir);
// }
