/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texturse_buff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:47:24 by aaitoual          #+#    #+#             */
/*   Updated: 2022/11/06 23:33:46 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

unsigned int	get_color(t_img img, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = 2 * (y * img.line_length) + 2 * (x * 4);
	ptr = img.addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

void	get_texture_buff(t_map *info)
{
	int		i;
	int		j;
	int		k;
	t_img	img1;

	img1.img = mlx_xpm_file_to_image(info->mlx, info->txt_ea, &j, &i);
	img1.addr = mlx_get_data_addr(img1.img, &img1.bits_per_pixel,
			&img1.line_length, &img1.endian);
	info->buff_ea = malloc(4 * i * j);
	k = 0;
	i = -1;
	while (++i < TILESIZE)
	{
		j = -1;
		while (++j < TILESIZE)
		{
			info->buff_ea[k] = get_color(img1, j, i);
			k++;
		}
	}
	mlx_destroy_image(info->mlx, img1.img);
	get_no_texture(info);
	get_we_texture(info);
	get_so_texture(info);
}

void	set_screen_pixel(t_img *img, int i, int j, int color)
{
	char	*ptr;

	ptr = img->addr + j * img->line_length + i *(img->bits_per_pixel / 8);
	*(unsigned int *)ptr = color;
}

void	ceilling_floor_render(t_map *mapp, int state, int color)
{
	t_img	img;
	int		side;

	if (state == 0)
		side = 0;
	else
		side = WIN_H / 2;
	img.img = mlx_new_image(mapp->mlx, WIN_W, WIN_H / 2);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	mapp->i = -1;
	while (++mapp->i != WIN_H / 2)
	{
		mapp->j = -1;
		while (++mapp->j != WIN_W)
		{
			set_screen_pixel(&img, mapp->j, mapp->i, color);
		}
	}
	mlx_put_image_to_window(mapp->mlx, mapp->win2, img.img, 0, side);
	mlx_destroy_image(mapp->mlx, img.img);
}
