/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:04:42 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/14 07:26:50 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	if (!len)
		return (0);
	while (*s1 && *s1 == *s2 && len - 1 > 0)
	{
		s1++;
		s2++;
		len--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_atoi(char *str)
{
	long long	res;
	long long	cas;
	int			sin;

	res = 0;
	sin = 1;
	if (ft_strcmp(str, "-2147483648") == 0)
		return (-2147483648);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sin = -1;
		str++;
	}
	while (*str && *str <= '9' && *str >= '0')
	{
		cas = res;
		res = res * 10 + *str++ - 48;
		if (cas != res / 10)
			return (ft_atoi_trois());
	}
	return (res * sin);
}

int	ft_atoi_trois(void)
{
	return (1);
}
