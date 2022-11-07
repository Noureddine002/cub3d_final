/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:15:37 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/07 19:37:12 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_player_pos(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map_grid[y])
	{
		x = 0;
		while (map->map_grid[y][x])
		{
			if (map->map_grid[y][x] == map->gamer)
			{
				map->player->pos_x = x;
				map->player->pos_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	initialize_player(t_map *mapp)
{
	get_player_pos(mapp);
	mapp->player->pos_x *= TILESIZE;
	mapp->player->pos_y *= TILESIZE;
	mapp->player->pos_x += TILESIZE / 2;
	mapp->player->pos_y += TILESIZE / 2;
	mapp->player->radius = 3.0;
	mapp->player->turndirec = 0;
	mapp->player->walkdir = 0;
	if (mapp->gamer == 'N')
		mapp->player->rot_nang = M_PI / 2;
	if (mapp->gamer == 'S')
		mapp->player->rot_nang = 3 * M_PI / 2;
	if (mapp->gamer == 'W')
		mapp->player->rot_nang = M_PI;
	if (mapp->gamer == 'E')
		mapp->player->rot_nang = 0;
	mapp->player->movespeed = 6.0;
	mapp->player->rotationspeed = 3 * (M_PI / 180);
	mapp->player->walkdirecside = 0;
}

void	initialize_rays(t_map *mapp)
{
	mapp->ray->pos_whor_hitx = 0;
	mapp->ray->pos_whor_hity = 0;
	mapp->ray->pos_wver_hitx = 0;
	mapp->ray->pos_wver_hity = 0;
	mapp->ray->distance_ray = 0;
	mapp->ray->down_dir = 0;
	mapp->ray->up_dir = 0;
	mapp->ray->right_dir = 0;
	mapp->ray->left_dir = 0;
	mapp->ray->column_id = 0;
}

void	initialize_xpm(t_map *mapp)
{
	mapp->mlx = mlx_init();
	mapp->ground = mlx_xpm_file_to_image(mapp->mlx, GROUD,
			&mapp->img_w, &mapp->img_h);
	if (!mapp->ground)
		exit(0);
	mapp->wall = mlx_xpm_file_to_image(mapp->mlx, WALL,
			&mapp->img_w, &mapp->img_h);
	if (!mapp->wall)
		exit(0);
	mapp->player->player = mlx_xpm_file_to_image(mapp->mlx, PLAYER,
			&mapp->img_w, &mapp->img_h);
	if (!mapp->player->player)
		exit(0);
	mapp->win2 = mlx_new_window(mapp->mlx, WIN_W,
			WIN_H, "./Cub3d");
	mapp->win = mlx_new_window(mapp->mlx, mapp->map_width_x * TILESIZE * 0.2,
			mapp->map_height_y * TILESIZE * 0.2, "./Cub3d_map");
}
