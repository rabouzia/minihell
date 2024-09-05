/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:54:36 by rabouzia          #+#    #+#             */
/*   Updated: 2023/12/19 16:25:28 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_memchr(const char *str, int c)
{
	unsigned char	*res;
	int				i;

	i = 0;
	res = (unsigned char *)str;
	while (*res)
	{
		if (*res == (unsigned char)c)
			return (res);
		res++;
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*r;
	int		d;

	if (!src)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!r)
		return (NULL);
	i = 0;
	d = 1;
	while (src[i] && d > 0)
	{
		if (src[i] == '\n')
			d--;
		r[i] = src[i];
		i++;
	}
	r[i] = 0;
	return (r);
}

char	*for_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	j = -1;
	if (!s1)
		return (ft_strdup(s2));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
		if (s2[j] == '\n')
			break ;
	}
	str[i] = '\0';
	return (free(s1), str);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
