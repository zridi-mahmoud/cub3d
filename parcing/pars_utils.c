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

int	ft_atoi(const char *s1)
{
	int	i;
	int	signe;
	int	sum;
	int	v;

	i = 0;
	v = 0;
	sum = 0;
	signe = 1;
	while (s1[i] == ' ' || (s1[i] >= 9 && s1[i] <= 13))
		i++;
	while (s1[i] == '-' || s1[i] == '+' )
	{
		if (s1[i] == '-')
			signe = signe * -1;
		i++;
		v++;
	}
	if (v > 1)
		return (0);
	while (ft_isdigit(s1[i]))
		sum = sum * 10 + s1[i++] - 48;
	return (sum * signe);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


static int	ft_count_split(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && c != s[i])
			i++;
		if (c == 0)
		{
			count++;
			break ;
		}
		while (c && c == s[i])
			i++;
		count++;
	}
	return (count);
}

static int	ft_count_word(char *s, char c)
{
	int	count;

	count = 0;
	while (*s && c != *s)
	{
		count++;
		s++;
	}
	return (count);
}

static char	*ft_word(char *s, char c, char **word)
{
	int	count;
	int	i;

	count = ft_count_word(s, c);
	*word = malloc((count + 1) * sizeof(char));
	if (!word)
		return (0);
	(*word)[count] = 0;
	i = 0;
	while (i < count)
		(*word)[i++] = *s++;
	while (c == *s)
		s++;
	return (s);
}

static int	_free(char **res, int size)
{
	while (size--)
	{
		free(res[size]);
	}
	free(res);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**res;
	int		count;	

	if (s == 0)
		return (NULL);
	i = 0;
	while (c && *s && c == (char) *s)
		s++;
	count = ft_count_split((char *)s, c);
	res = malloc((count + 1) * sizeof(char *));
	if (!res)
		return (0);
	res[count] = 0;
	i = 0;
	while (i < count)
	{
		s = ft_word((char *)s, c, res + i);
		if (!s)
			_free(res, i);
		i++;
	}
	return (res);
}