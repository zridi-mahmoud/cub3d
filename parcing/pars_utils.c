/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:20:02 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 01:39:21 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
