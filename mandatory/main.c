/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:09:10 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 18:56:47 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	allocate_map(t_map *map)
{
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		exit(0);
	map->ray = malloc(sizeof(t_ray) * WIN_W);
	if (!map->ray)
		exit(0);
	map->colors = malloc(sizeof(t_colors));
	if (!map->colors)
		exit(0);
}

void	free_map(t_map *map)
{
	free(map->colors);
	free(map->ray);
	free(map->player);
	free(map->buff_ea);
	free(map->buff_we);
	free(map->buff_no);
	free(map->buff_so);
	free(map);
}

int	main(int ac, char **av)
{
	t_map	*mapp;
	int		fd_map;
	char	**mape;

	mapp = malloc(sizeof(t_map));
	if (!mapp)
		exit(1);
	allocate_map(mapp);
	if (ac == 2)
	{
		if (!check_extension(av[1]))
			return (printf("bad extension !"), 0);
		fd_map = open(av[1], O_RDONLY);
		if (fd_map == -1)
			return (printf("File not Found\n"), close(fd_map), 1);
		mape = get_map(fd_map);
		if (!check_map_ressources(mape, mapp))
			exit(0);
		else
			game_start(mape, mapp);
	}
	else
		write(1, "wrong number or type of args", 28);
	free_map(mapp);
	return (0);
}
