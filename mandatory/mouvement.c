/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:02:39 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 20:22:03 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	close_window(int key, void *param)
{
	(void)key;
	(void)param;
	write(1, "\nGAME OVER", 10);
	exit(0);
}

int	key_down(int key, t_map *mapp)
{
	if (key == KEY_W)
		mapp->player->walkdir = 1;
	if (key == KEY_S)
		mapp->player->walkdir = -1;
	if (key == KEY_A)
		mapp->player->walkdirecside = 1;
	if (key == KEY_D)
		mapp->player->walkdirecside = -1;
	if (key == KEY_LEFT)
		mapp->player->turndirec = -1;
	if (key == KEY_RIGHT)
		mapp->player->turndirec = +1;
	if (key == KEY_CLOSE)
	{
		write(1, "\nGAME OVER", 10);
		exit(0);
	}
	return (1);
}

int	key_up(int key, t_map *mapp)
{
	if (key == KEY_W)
		mapp->player->walkdir = 0;
	if (key == KEY_S)
		mapp->player->walkdir = 0;
	if (key == KEY_A)
		mapp->player->walkdirecside = 0;
	if (key == KEY_D)
		mapp->player->walkdirecside = 0;
	if (key == KEY_LEFT)
		mapp->player->turndirec = 0;
	if (key == KEY_RIGHT)
		mapp->player->turndirec = 0;
	return (1);
}

void	get_x_y_val(t_map *mapp, double *x, double *y)
{
	*x = mapp->player->pos_x;
	*y = mapp->player->pos_y;
	*x += (cos(mapp->player->rot_nang)
			* mapp->player->walkdir
			+ sin(mapp->player->rot_nang)
			* mapp->player->walkdirecside) * 3;
	*y += (sin(mapp->player->rot_nang)
			* mapp->player->walkdir
			- cos(mapp->player->rot_nang)
			* mapp->player->walkdirecside) * 3;
}

void	move_player(t_map *mapp)
{
	double	x;
	double	y;

	get_x_y_val(mapp, &x, &y);
	mapp->player->rot_nang += mapp->player->turndirec
		* mapp->player->rotationspeed;
	if (mapp->map_grid[(int)floor(y) / TILESIZE]
		[(int)floor(x) / TILESIZE] != '1'
		&& mapp->map_grid[(int)floor(y) / TILESIZE]
		[(int)floor(x + 3) / TILESIZE] != '1'
		&& mapp->map_grid[(int)floor(y) / TILESIZE]
		[(int)floor(x - 3) / TILESIZE] != '1'
		&& mapp->map_grid[(int)floor(y + 3) / TILESIZE]
		[(int)floor(x) / TILESIZE] != '1'
		&& mapp->map_grid[(int)floor(y - 3) / TILESIZE]
		[(int)floor(x) / TILESIZE] != '1')
	{
		mapp->player->pos_x = x;
		mapp->player->pos_y = y;
	}
}
