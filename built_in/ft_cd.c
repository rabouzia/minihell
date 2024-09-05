/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:39:36 by rabouzia          #+#    #+#             */
/*   Updated: 2024/07/12 23:01:48 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(const char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	print_too_many_arguments_error(void)
{
	ft_putstr_fd("kashell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(": too many arguments\n", 2);
}

static int	handle_cd_errors(int cnt)
{
	if (cnt > 2)
	{
		print_too_many_arguments_error();
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_cd(const char *cmd, const char **args, t_env *env)
{
	int		cnt;

	cnt = count_args(args);
	(void)cmd;
	init_oldpwd_node(env);
	if (!args[1])
		return (chdir_to_home(env), SUCCESS);
	if (handle_cd_errors(cnt) == FAILURE)
		return (FAILURE);
	if (!change_dir(args[1], env))
		return (FAILURE);
	return (SUCCESS);
}

// void	modify_pwd_in_env(t_env *env, char *str)
// {
// 	char	*new_pwd;
// 	char	*last_slash;

// 	if (str && *str != '\0')
// 	{
// 		new_pwd = ft_strjoin(env->pwd, str);
// 		free(env->pwd);
// 		env->pwd = new_pwd;
// 	}
// 	else
// 	{
// 		last_slash = strrchr(env->pwd, '/');
// 		if (last_slash)
// 			*last_slash = '\0';
// 	}
// }
