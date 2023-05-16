/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:43:35 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 17:37:21 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *s)
{
	int	i;	

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;
	int		l;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = 0;
	}
	l = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (l + 1));
	while (s1[i] != 0 && s1[i] != '\n')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = 0;
	free(s1);
	return (result);
}

int	check_line(char **line, char *buffer)
{
	if (buffer[0] == '\n')
	{
		*line = ft_strjoin(*line, buffer);
		free(buffer);
		return (0);
	}
	if (buffer[0] == '\0')
	{
		free(buffer);
		return (0);
	}
	*line = ft_strjoin(*line, buffer);
	return (1);
}

char	*get_line(int fd)
{
	char	*line;
	char	*buffer;
	int		a;

	buffer = (char *)malloc(sizeof(char) * 2);
	line = NULL;
	while (1)
	{
		a = read(fd, buffer, 1);
		if (a == -1)
		{
			if (buffer)
				free(buffer);
			return (NULL);
		}
		if (a == 0)
		{
			free(buffer);
			return (line);
		}
		buffer[1] = 0;
		if (!check_line(&line, buffer))
			return (line);
	}
	return (free(buffer), line);
}

char	*get_next_line(int fd)
{
	char	*result;

	if (fd < 0)
		return (NULL);
	result = get_line(fd);
	return (result);
}
