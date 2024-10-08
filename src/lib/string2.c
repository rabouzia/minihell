/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:54:33 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/08 17:50:42 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_strncat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t j;

	if (!src)
		return ;
	i = ft_strlen(dst);
	j = 0;
	while (src[j] && j < size)
		dst[i++] = src[j++];
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

void ft_putstr_fd(char *str, int fd)
{
	int i;
	i = 0;
	while(str[i])
		write(fd, &str[i++], 1);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
