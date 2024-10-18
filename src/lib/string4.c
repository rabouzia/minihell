/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:34:25 by rabouzia          #+#    #+#             */
/*   Updated: 2024/10/18 17:10:59 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	*ft_calloc(size_t n, size_t s)
{
	char	*str;
	size_t	i;

	i = 0;
	if (s != 0)
	{
		if (n > INT_MAX / s)
			return (0);
	}
	str = (char *)malloc(n * s);
	if (str == 0)
		return (0);
	while (i < n * s)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}

char	*ft_itoa(int n)
{
	long int	nb;
	size_t		len;
	char		*ret;

	nb = n;
	len = n == 0;
	if (nb < 0 && ++len)
		nb = -nb;
	while (n && ++len)
		n /= 10;
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	*ret = '-';
	if (!nb)
		*ret = '0';
	while (nb)
	{
		ret[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (ret);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}
