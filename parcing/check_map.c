/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-maza <rel-maza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:05:43 by rel-maza          #+#    #+#             */
/*   Updated: 2023/05/16 23:19:13 by rel-maza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_file(char *filename, t_cub3D *cub)
{
	cub->fd = open(filename, O_RDONLY);
	if (cub->fd == -1)
	{
		printf("Error: could not open file.\n");
		exit(1);
	}
}

void	check_forma(t_cub3D *cub, t_line *tmp)
{
	if (ft_sortpathtexture(cub) || ft_checkifclosed(cub, tmp))
	{
		printf("❌Error.\n");
		exit(0);
	}
	if (ft_checkformultiplemap(cub))
	{
		printf("❌Error.\n");
		exit(0);
	}
	if (ft_checkforspaces(cub) || ft_countpathtexture(cub) || \
		ft_checkforplayer(cub) || ft_colorparce(cub))
	{
		printf("❌Error.\n");
		exit(0);
	}
}

void	hooks(t_var *data)
{
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, &key_release, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
}

t_line	*read_map(t_cub3D *cub)
{
	t_line	*new_node;
	t_line	*current;
	t_line	*head;
	char	*line;

	head = NULL;
	line = get_next_line(cub->fd);
	while (line)
	{
		new_node = (t_line *)malloc(sizeof(t_line));
		new_node->line = ft_strdup(line);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
	return (head);
}

int	is_valid_map( char *filename)
{
	t_var	*data;
	t_cub3D	*cub;
	t_line	*head;
	t_line	*tmp;

	data = malloc(sizeof(t_var));
	cub = malloc(sizeof(t_cub3D));
	check_file(filename, cub);
	head = read_map(cub);
	tmp = head;
	cub->max_lenght = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->line) > cub->max_lenght)
			cub->max_lenght = ft_strlen(tmp->line);
		tmp = tmp->next;
	}
	tmp = head;
	if (!filling(cub, tmp))
		return (0);
	data = init_data(cub);
	if (data == NULL)
		return (1);
	hooks(data);
	return (1);
}
