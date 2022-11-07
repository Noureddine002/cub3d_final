/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:50:15 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 18:56:42 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_player(t_map *mapp)
{
	mlx_put_image_to_window(mapp->mlx, mapp->win, mapp->player->player,
		mapp->player->pos_x, mapp->player->pos_y);
}

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	draw_map(t_map *mapp)
{
	mlx_clear_window(mapp->mlx, mapp->win2);
	move_player(mapp);
	castallrays(mapp);
	ceilling_floor_render(mapp, 0, create_rgb(mapp->colors->ceilling[0], \
	mapp->colors->ceilling[1], mapp->colors->ceilling[2]));
	ceilling_floor_render(mapp, 1, create_rgb(mapp->colors->floor[0], \
	mapp->colors->floor[1], mapp->colors->floor[2]));
	projectewall3d(mapp);
	return (0);
}

void	initialize(t_map *mapp)
{
	initialize_xpm(mapp);
	initialize_player(mapp);
	initialize_rays(mapp);
}

void	game_start(char **grid, t_map *mapp)
{	
	mapp->map_grid = true_map(mapp, grid);
	initialize(mapp);
	get_texture_buff(mapp);
	draw_map(mapp);
	mlx_hook(mapp->win2, 2, 0, &key_down, mapp);
	mlx_hook(mapp->win2, 3, 0, &key_up, mapp);
	mlx_hook(mapp->win2, EVENT_CLOSE, 0L, close_window, mapp);
	mlx_loop_hook(mapp->mlx, &draw_map, mapp);
	mlx_loop(mapp->mlx);
}
