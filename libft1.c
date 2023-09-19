/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 06:24:46 by stemsama          #+#    #+#             */
/*   Updated: 2023/09/19 18:59:57 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	cheek_set(const char c_s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c_s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	get_first_p(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && cheek_set(s1[i], set) == 1)
	{
		i++;
	}
	return (i);
}

static int	get_last_p(char *s1, char *set)
{
	int	j;

	j = ft_strlen(s1) - 1 ;
	while (j >= 0 && cheek_set(s1[j], set) == 1)
	{
		j--;
	}
	return (j);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*p;
	int		fin;
	int		fst;
	int		len;
	int		i;

	i = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	fst = get_first_p(s1, set);
	fin = get_last_p(s1, set);
	len = fin - fst + 1;
	if (fst == (int)ft_strlen(s1))
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s1[fst];
		i += 1;
		fst += 1;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strtrim_free(char *s1, char *set)
{
	char	*p;
	int		fin;
	int		fst;
	int		len;
	int		i;

	i = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	fst = get_first_p(s1, set);
	fin = get_last_p(s1, set);
	len = fin - fst + 1;
	if (fst == (int)ft_strlen(s1))
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (i < len)
		p[i++] = s1[fst++];
	p[i] = '\0';
	free(s1);
	s1 = NULL;
	return (p);
}
