# include "../cub3d.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}


char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*p;

	p = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (p == NULL)
		return (0);
	ft_strcpy(p, src);
	return (p);
}



static int	ft_count(char *dest)
{
	int	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	d;

	d = ft_count(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[d] = src[i];
		d++;
		i++;
	}
	dest[d] = '\0';
	return (dest);
}

static int	min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t			lenght;
	char			*p;
	size_t			size;

	if (s == NULL)
		return (0);
	lenght = ft_strlen(s);
	if (start >= lenght)
		size = 0;
	else
		size = min(lenght - start, len);
	p = malloc(sizeof(*s) * (size + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s + start, size + 1);
	return (p);
}

static int	ft_check(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char **s1, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((*s1) == NULL)
		return (0);
	while ((*s1)[i])
	{
		if (ft_check(set, (*s1)[i]) == 1)
			i++;
		else
			break ;
	}
	j = ft_strlen((*s1)) - 1;
	while (j > 0)
	{
		if (ft_check(set, (*s1)[j]) == 1)
			j--;
		else
			break ;
	}
	return (ft_substr((*s1), i, (j + 1) - i));
}
