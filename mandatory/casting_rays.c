/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 23:25:12 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/11/06 23:38:04 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	horz_wall_util(t_player *player, t_ray *ray, t_var *var)
{
	var->yintercept = floor(player->pos_y / TILESIZE) * TILESIZE ;
	if (ray->down_dir)
		var->yintercept += TILESIZE;
	var->xintercept = player->pos_x + (var->yintercept
			- player->pos_y) / tan(ray->rayang);
	var->ystep = TILESIZE;
	if (ray->up_dir)
		var->ystep *= -1;
	var->xstep = TILESIZE / tan(ray->rayang);
	if (ray->left_dir && var->xstep > 0)
		var->xstep *= -1;
	if (ray->right_dir && var->xstep < 0)
		var->xstep *= -1;
	var->next_x = var->xintercept;
	var->next_y = var->yintercept;
	if (ray->up_dir)
		var->next_y--;
}

void	horz_wall(t_map *mapp, t_player *player, t_ray *ray, t_var *var)
{
	horz_wall_util(player, ray, var);
	while ((var->next_x >= 0 && var->next_x <= (mapp->map_width_x * TILESIZE))
		&& (var->next_y >= 0 && var->next_y <= (mapp->map_height_y * TILESIZE)))
	{
		if (is_wall(mapp, var->next_x, var->next_y, '1'))
		{
			ray->horr_line = 1;
			ray->pos_whor_hitx = var->next_x;
			ray->pos_whor_hity = var->next_y;
			break ;
		}
		else
		{
			var->next_x += var->xstep;
			var->next_y += var->ystep;
		}
	}
}

void	vert_wall_util(t_player *player, t_ray *ray, t_var *var)
{
	var->xintercept = floor(player->pos_x / TILESIZE) * TILESIZE;
	if (ray->right_dir)
		var->xintercept += TILESIZE;
	var->yintercept = player->pos_y + (var->xintercept
			- player->pos_x) * tan(ray->rayang);
	var->xstep = TILESIZE;
	if (ray->left_dir)
		var->xstep *= -1;
	var->ystep = TILESIZE * tan(ray->rayang);
	if (ray->up_dir && var->ystep > 0)
		var->ystep *= -1;
	if (ray->down_dir && var->ystep < 0)
		var->ystep *= -1;
	var->next_xv = var->xintercept;
	var->next_yv = var->yintercept;
	if (ray->left_dir)
		var->next_xv--;
}

void	vert_wall(t_map *mapp, t_player *player, t_ray *ray, t_var *var)
{
	vert_wall_util(player, ray, var);
	while (var->next_xv >= 0 && var->next_xv <= (mapp->map_width_x * TILESIZE)
		&& var->next_yv >= 0 && var->next_yv <= (mapp->map_height_y * TILESIZE))
	{
		if (is_wall(mapp, var->next_xv, var->next_yv, '1'))
		{
			ray->vert_line = 1;
			ray->pos_wver_hitx = var->next_xv;
			ray->pos_wver_hity = var->next_yv;
			break ;
		}
		else
		{
			var->next_xv += var->xstep;
			var->next_yv += var->ystep;
		}
	}
}

void	casting(t_map *mapp, t_player *player, t_ray *ray)
{
	t_var	var;

	ray->horr_line = 0;
	ray->vert_line = 0;
	horz_wall(mapp, player, ray, &var);
	vert_wall(mapp, player, ray, &var);
	if (ray->horr_line)
		var.hor_hitdis = (distancepythagoras(mapp->player->pos_x,
					mapp->player->pos_y, var.next_x, var.next_y));
	else
		var.hor_hitdis = INT_MAX;
	if (ray->vert_line)
		var.ver_hitdis = (distancepythagoras(mapp->player->pos_x,
					mapp->player->pos_y, var.next_xv, var.next_yv));
	else
		var.ver_hitdis = INT_MAX;
	if (var.hor_hitdis < var.ver_hitdis)
		set_hor_distance(ray, &var);
	if (var.hor_hitdis > var.ver_hitdis)
		set_vert_distance(ray, &var);
}
