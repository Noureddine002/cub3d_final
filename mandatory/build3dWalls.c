/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build3dWalls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:09:10 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 21:15:11 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	*get_texturse_info(t_map *m, int i, int *ix)
{	
	if (m->ray[i / 3].horr_line)
	{
		*ix = ((int)(m->ray[i / 3].pos_whor_hitx) % TILESIZE);
		if (m->ray[i / 3].down_dir)
			return (m->buff_so);
		else
			return (m->buff_no);
	}
	else
	{
		*ix = ((int)(m->ray[i / 3].pos_wver_hity) % TILESIZE);
		if (m->ray[i / 3].right_dir)
			return (m->buff_ea);
		else
			return (m->buff_we);
	}
}

void	initialize_img(t_map *m, t_img *img, int wall_h)
{
	img->img = mlx_new_image(m->mlx, 3, wall_h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	put_wall(t_map *m, int wall_h, int i)
{
	t_img	img;
	char	*dst;
	t_var	var;

	initialize_img(m, &img, wall_h);
	var.ptw_buffer = get_texturse_info(m, i, &var.ptw_ix);
	var.ptw_y = 0;
	while (var.ptw_y != wall_h)
	{
		var.ptw_iy = (var.ptw_y) * ((TILESIZE / (double)wall_h));
		var.ptw_x = 0;
		while (var.ptw_x != 3)
		{
			dst = (img.addr + (var.ptw_y * img.line_length
						+ var.ptw_x * (img.bits_per_pixel / 8)));
			*(unsigned int *) dst = var.ptw_buffer[(TILESIZE
					* var.ptw_iy) + var.ptw_ix];
			var.ptw_x++;
		}
		var.ptw_y++;
	}
	mlx_put_image_to_window(m->mlx, m->win2, img.img, i,
		(WIN_H / 2) - (wall_h / 2));
	mlx_destroy_image(m->mlx, img.img);
}

void	projectewall3d(t_map *m)
{
	int		i;
	double	raydist;
	double	wallstripheigth;
	double	distanceprojplan;

	i = 0;
	distanceprojplan = (WIN_W / 2) / tan(FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		raydist = m->ray[i].distance_ray
			* cos(m->ray[i].rayang - m->player->rot_nang);
		wallstripheigth = (TILESIZE / raydist) * distanceprojplan;
		put_wall(m, (int)fabs((wallstripheigth)), i * 3);
		i++;
	}
}
