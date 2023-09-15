/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:35:47 by osarsar           #+#    #+#             */
/*   Updated: 2023/01/16 13:35:53 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*split_line(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	dest = malloc((i + 2));
	if (!dest)
		return (0);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	if (str[i] != '\0')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

char	*static_line(char *str)
{
	size_t	i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (0);
	}
	dest = malloc(ft_strlen(str) - i + 1);
	if (!dest)
		return (0);
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(str);
	str = NULL;
	return (dest);
}

char	*full_line(char *str, int fd)
{
	char	*mybuffer;
	int		count;

	count = 2023;
	mybuffer = malloc(BUFFER_SIZE + 1);
	if (!mybuffer)
		return (0);
	while (!ft_strchr(str, '\n') && count)
	{
		count = read(fd, mybuffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(mybuffer);
			free(str);
			return (0);
		}
		if (mybuffer[count] != '\0')
			mybuffer[count] = '\0';
		str = ft_strjoin(str, mybuffer);
	}
	free (mybuffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*myregister;
	char		*myline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	myregister = full_line(myregister, fd);
	if (!myregister)
		return (0);
	myline = split_line(myregister);
	myregister = static_line(myregister);
	return (myline);
}
