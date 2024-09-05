/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd_oldpwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:55:56 by junsan            #+#    #+#             */
/*   Updated: 2024/07/16 08:25:17 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_pwd_oldpwd(t_env *env)
{
	char	*tmp;

	tmp = env->pwd->content;
	env->pwd->content = env->old_pwd->content;
	env->old_pwd->content = tmp;
}

void	update_pwd_oldpwd(t_env *env, const char *new_pwd)
{
	t_env	*cur;

	cur = env;
	if (env->old_pwd->content)
		free(env->old_pwd->content);
	env->old_pwd->content = env->pwd->content;
	env->pwd->content = ft_strdup((char *)new_pwd);
	while (cur)
	{
		if (ft_strncmp(cur->name, "OLDPWD", 6) == 0)
		{
			if (cur->content)
				free(cur->content);
			cur->content = ft_strdup(env->old_pwd->content);
		}
		else if (ft_strncmp(cur->name, "PWD", 3) == 0)
		{
			if (cur->content)
				free(cur->content);
			cur->content = ft_strdup(env->pwd->content);
		}
		cur = cur->next;
	}
}

void	init_pwd_oldpwd_nodes(t_env *head, t_env *old_pwd, t_env *pwd)
{
	if (old_pwd)
		add_pwd_oldpwd(head, old_pwd->name, old_pwd->content);
	else
		add_pwd_oldpwd(head, "OLDPWD", NULL);
	if (pwd)
		add_pwd_oldpwd(head, pwd->name, pwd->content);
	else
		add_pwd_oldpwd(head, "PWD", NULL);
}

int	init_oldpwd_node(t_env *lst)
{
	t_env	*head;
	t_env	*old_pwd;
	t_env	*pwd;

	head = lst;
	if (!head)
		return (0);
	old_pwd = NULL;
	pwd = NULL;
	while (lst)
	{
		if (ft_strncmp(lst->name, "OLDPWD", 6) == 0)
			old_pwd = lst;
		else if (ft_strncmp(lst->name, "PWD", 3) == 0)
			pwd = lst;
		lst = lst->next;
	}
	init_pwd_oldpwd_nodes(head, pwd, old_pwd);
	return (0);
}

void	add_pwd_oldpwd(t_env *head, const char *name, const char *content)
{
	if (ft_strncmp(name, "OLDPWD", 6) == 0)
	{
		if (content)
		{
			if (head->old_pwd->content)
				free(head->old_pwd->content);
			head->old_pwd->content = ft_strdup(content);
		}
		else
			head->old_pwd->content = NULL;
	}
	if (ft_strncmp(name, "PWD", 3) == 0)
	{
		if (content)
		{
			if (head->pwd->content)
				free(head->pwd->content);
			head->pwd->content = ft_strdup(content);
		}
		else
			head->pwd->content = NULL;
	}
}
