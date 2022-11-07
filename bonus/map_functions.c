/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:50:15 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 03:16:55 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_player(t_map *mapp)
{
	mlx_put_image_to_window(mapp->mlx, mapp->win, mapp->player->player,
		mapp->player->pos_x * 0.2, mapp->player->pos_y * 0.2);
}

void	draw_minimap(t_map *mapp)
{
	t_img	img;
	int		j;
	int		k;

	img.img = mlx_new_image(mapp->mlx, mapp->map_width_x * TILESIZE * 0.2,
			mapp->map_height_y * TILESIZE * 0.2);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	j = 0;
	k = 0;
	while (mapp->map_grid[j])
	{
		k = -1;
		while (mapp->map_grid[j][++k])
			draw_square(k * TILESIZE * 0.2, j * TILESIZE
				* 0.2, mapp->map_grid[j][k], &img);
		j++;
	}
	mlx_put_image_to_window(mapp->mlx, mapp->win, img.img, 0, 0);
	mlx_destroy_image(mapp->mlx, img.img);
}

int	draw_map(t_map *mapp)
{	
	mlx_clear_window(mapp->mlx, mapp->win2);
	mlx_clear_window(mapp->mlx, mapp->win);
	draw_minimap(mapp);
	move_player(mapp);
	castallrays(mapp);
	draw_player(mapp);
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
