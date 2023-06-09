/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:18:24 by admansar          #+#    #+#             */
/*   Updated: 2022/10/20 18:56:54 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_counter(int k)
{
	int	i;

	i = 0;
	if (k <= 0)
		i++;
	while (k != 0)
	{
		i++;
		k = k / 10;
	}
	return (i);
}

void	converter(char *p, long int i, long int a)
{
	while (a != 0)
	{
		p[i] = (a % 10) + 48;
		i--;
		a = a / 10;
	}
}

char	*ft_itoa(int n)
{
	long int	j;
	char		*ptr;
	long int	s;

	s = (long int)n;
	j = ft_counter(s);
	ptr = malloc(j + 1);
	if (!ptr)
		return (0);
	ptr[j] = '\0';
	j--;
	if (s == 0)
		ptr[0] = '0';
	else if (s < 0)
	{
		s = (-1) * s;
		ptr[0] = '-';
	}
	converter(ptr, j, s);
	return (ptr);
}
