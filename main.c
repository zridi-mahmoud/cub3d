/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:54:54 by mzridi            #+#    #+#             */
/*   Updated: 2023/05/16 01:43:10 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s <map file>\n", av[0]);
		return (1);
	}
	if (is_valid_map(av[1]))
		printf("Map is valid.\n");
	else
		printf("❌ Map is invalid.\n");
	return (0);
}
