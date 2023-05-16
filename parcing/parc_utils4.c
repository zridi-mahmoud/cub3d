/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:24:13 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 01:39:13 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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
