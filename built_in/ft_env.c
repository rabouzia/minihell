/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:48:50 by junsan            #+#    #+#             */
/*   Updated: 2024/07/15 15:27:35 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_env(t_env *list)
{
	t_env	*cur;

	cur = list;
	while (cur)
	{
		if (!cur->content)
		{
			cur = cur->next;
			continue ;
		}
		else
			printf("%s=%s\n", cur->name, cur->content);
		cur = cur->next;
	}
}

// status_exit == 0 SUCCESS status_exit == 1 FAILURE
static int	check_in_env(const char *arg, t_env *list)
{
	t_env	*cur;

	cur = list;
	while (cur)
	{
		if ((ft_strncmp(arg, cur->name, ft_strlen(cur->name)) == 0))
		{
			ft_putstr_fd(cur->content, 1);
			printf_env(list);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

// UnCompleted
int	ft_env(const char *cmd, const char **args, t_env *list)
{
	int	i;

	(void)cmd;
	i = 0;
	if (args[1] == NULL)
	{
		printf_env(list);
		return (SUCCESS);
	}
	else
	{
		while (args[++i])
		{
			if (!check_in_env(args[i], list))
			{
				ft_putstr_fd("ignoring non-option arguments\n", STDOUT_FILENO);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

// void	env_split(const char *str, char **name, char **content)
// {
// 	size_t	i;
// 	size_t	j;

// 	if (!str)
// 		return ;
// 	i = 0;
// 	j = 1;
// 	// tmp = 0;
// 	while (str[i] != '=')
// 		i++;
// 	*name = ft_strndup(str, i);
// 	i++;
// 	j = i;
// 	while (str[i])
// 		i++;
// 	*content = ft_strndup(str, i - j);
// }

// t_env	*fill_env(int ac, char **av, char **env)
// {
// 	char	*name;
// 	char	*content;
// 	t_env	*arg;
// 	t_env	*tmp;
// 	int		i;

// 	(void)ac;
// 	(void)av;
// 	arg = ft_calloc(1, sizeof(t_env));
// 	if (!arg)
// 		return (NULL);
// 	i = -1;
// 	name = NULL;
// 	content = NULL;
// 	tmp = arg;
// 	while (env[++i])
// 	{
// 		env_split(env[i], &name, &content);
// 		add_builtin_node(&tmp, name, content);
// 		free(name);
// 		free(content);
// 	}
// 	arg = tmp;
// 	return (arg);
// }
