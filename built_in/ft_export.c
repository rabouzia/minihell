/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:38:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/07/15 15:57:42 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_show(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (!cur->content)
			printf("export %s\n", cur->name);
		else
			printf("export %s=%s\n", cur->name, cur->content);
		cur = cur->next;
	}
}

static void	handle_invalid_identifier(const char *arg)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

int	ft_export(const char *cmd, const char **args, t_env *list)
{
	int		i;
	char	*name;
	char	*content;

	(void)cmd;
	content = NULL;
	name = NULL;
	if (!args[1])
		return (ft_export_show(list), SUCCESS);
	i = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
			env_split(args[i], &name, &content);
		else
			name = ft_strdup((char *)args[i]);
		if (!change_var_if_exist(name, content, list))
		{
			if (check_first_arg(args[i][0]))
				handle_invalid_identifier(args[i]);
			else
				add_builtin_node(&list, name, content);
		}
	}
	return (SUCCESS);
}
