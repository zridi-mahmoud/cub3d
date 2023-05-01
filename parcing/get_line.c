#include "../cub3d.h"

int ft_strlen(char *s)
{
	if (!s)
		return (0);
	int i;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *result = NULL;
	int l = 0;
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
char *get_line(int fd)
{
	char *line = NULL;
	char *buffer = NULL;
	int a;
	buffer = (char *)malloc(sizeof(char) * 2);
	while (1)
	{
		a = read(fd, buffer, 1);
		if (a == -1)
		{
			if (buffer)
				free(buffer);
			free(line);
			return (NULL);
		}
		if (a == 0)
		{
			free(buffer);
			return (line);
		}
		buffer[1] = 0;
		if (buffer[0] == '\n')
		{
			line = ft_strjoin(line, buffer);
			free(buffer);
			return (line);
		}
		if (buffer[0] == '\0')
		{
			free(buffer);
			return (line);
		}
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}
char *get_next_line(int fd)
{

	char *result = NULL;

	if (fd < 0)
		return (NULL);

	result = get_line(fd);
	return (result);
}