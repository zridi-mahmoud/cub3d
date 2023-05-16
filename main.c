/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:54:54 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/17 00:32:18 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] - (unsigned char)s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s <map file>\n", av[0]);
		return (1);
	}
	if (ft_strlen(av[1]) < 4
		|| ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		printf("❌ Map is invalid.\n");
		return (1);
	}
	if (is_valid_map(av[1]))
		printf("Map is valid.\n");
	else
		printf("❌ Map is invalid.\n");
	return (0);
}
