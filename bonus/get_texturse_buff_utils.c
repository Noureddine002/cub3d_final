/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texturse_buff_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:07:18 by aaitoual          #+#    #+#             */
/*   Updated: 2022/11/07 19:37:25 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_no_texture(t_map *info)
{
	int		i;
	int		j;
	int		k;
	t_img	img1;
	int		*buff;

	img1.img = mlx_xpm_file_to_image(info->mlx, info->txt_no, &j, &i);
	if (!img1.img)
		exit(0);
	img1.addr = mlx_get_data_addr(img1.img, &img1.bits_per_pixel,
			&img1.line_length, &img1.endian);
	buff = malloc(4 * i * j);
	k = 0;
	i = -1;
	while (++i < TILESIZE)
	{
		j = -1;
		while (++j < TILESIZE)
		{
			buff[k] = get_color(img1, j, i);
			k++;
		}
	}
	info->buff_no = buff;
	mlx_destroy_image(info->mlx, img1.img);
}

void	get_we_texture(t_map *info)
{
	int		i;
	int		j;
	int		k;
	t_img	img1;
	int		*buff;

	img1.img = mlx_xpm_file_to_image(info->mlx, info->txt_we, &j, &i);
	if (!img1.img)
		exit(0);
	img1.addr = mlx_get_data_addr(img1.img, &img1.bits_per_pixel,
			&img1.line_length, &img1.endian);
	buff = malloc(4 * i * j);
	k = 0;
	i = -1;
	while (++i < TILESIZE)
	{
		j = -1;
		while (++j < TILESIZE)
		{
			buff[k] = get_color(img1, j, i);
			k++;
		}
	}
	info->buff_we = buff;
	mlx_destroy_image(info->mlx, img1.img);
}

void	get_so_texture(t_map *info)
{
	int		i;
	int		j;
	int		k;
	t_img	img1;
	int		*buff;

	img1.img = mlx_xpm_file_to_image(info->mlx, info->txt_so, &j, &i);
	if (!img1.img)
		exit(0);
	img1.addr = mlx_get_data_addr(img1.img, &img1.bits_per_pixel,
			&img1.line_length, &img1.endian);
	buff = malloc(4 * i * j);
	k = 0;
	i = -1;
	while (++i < TILESIZE)
	{
		j = -1;
		while (++j < TILESIZE)
		{
			buff[k] = get_color(img1, j, i);
			k++;
		}
	}
	info->buff_so = buff;
	mlx_destroy_image(info->mlx, img1.img);
}
