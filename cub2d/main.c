/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:38:40 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/08 18:04:25 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

float	distancebetwenpoint(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float   normlize(float rayngle)
{
    rayngle = remainder(rayngle, 2 * PI);
    if (rayngle < 0)
        rayngle = (2 * PI) + rayngle;
    return (rayngle);
}

void    draw_line(t_cub *data, float x, float y, float x2, float y2, int color)
{
    int dx;
    int dy;
    float xinc;
    float yinc;
    float step;
    dx = x2 - x;
    dy = y2 - y;
    step = fmaxf(abs(dy), abs(dx));
    xinc = dx / step;
    yinc = dy / step;
    while (step >= 0)
    {
        mlx_pixel_put(data->init, data->win, round(x), round(y), color);
        x += xinc;
        y += yinc;
        step--;
    }
}

void    cast(t_cub *data, t_player *player, t_rays ray)
{
    float xintersept;
    float yintersept;
    float xstep;
    float ystep;
    float nextx, nextx2;
    float nexty, nexty2;

    ray.isHor = 0;
    ray.isVer = 0;
    ////////// horizontal hit
    yintersept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    if (ray.facingdown)
        yintersept += TILE_SIZE ;
    xintersept = player->x + (yintersept - player->y) / tan(ray.rayangle);
    ystep = TILE_SIZE;
    if (ray.facingup)
        ystep *= -1;
    xstep = TILE_SIZE / tan(ray.rayangle);
    if (ray.facingleft && xstep > 0)
        xstep *= -1;
    if (ray.facingright && xstep < 0)
        xstep *= -1;
    nextx = xintersept;
    nexty = yintersept;
    if (ray.facingup)
        nexty--;
    while (nextx >= 0 && nextx <= WINDOW_WIDTH && nexty >= 0 && nexty <= WINDOW_HEIGHT)
    {
        if (data->map[(int)floor(nexty / TILE_SIZE)][(int)floor(nextx / TILE_SIZE)] == '1')
        {
            ray.isHor = 1;
            break ;
        }
        else{
            nextx += xstep;
            nexty += ystep;
        }
    }
    ///////// vertical hit
    xintersept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    if (ray.facingright)
        xintersept += TILE_SIZE ;
    yintersept = player->y + (xintersept - player->x) * tan(ray.rayangle);
    
    xstep = TILE_SIZE;
    if (ray.facingleft)
        xstep *= -1;
    ystep = TILE_SIZE * tan(ray.rayangle);
    if (ray.facingup && ystep > 0)
        ystep *= -1;
    if (ray.facingdown && ystep < 0)
        ystep *= -1;
    nextx2 = xintersept;
    nexty2 = yintersept;
    if (ray.facingleft)
        nextx2--;
    while (nextx2 >= 0 && nextx2 <= WINDOW_WIDTH && nexty2 >= 0 && nexty2 <= WINDOW_HEIGHT)
    {
        if (data->map[(int)floor(nexty2 / TILE_SIZE)][(int)floor(nextx2 / TILE_SIZE)] == '1')
        {
            ray.isVer = 1;
            break ;
        }
        else{
            nextx2 += xstep;
            nexty2 += ystep;
        }
    }
    float hdist;
    float vdist;
    float hitx;
    float hity;
    if (ray.isHor)
        hdist = distancebetwenpoint(data->player->x , data->player->y, nextx, nexty);
    else
        hdist = INT_MAX;
    if (ray.isVer)
        vdist = distancebetwenpoint(data->player->x , data->player->y, nextx2, nexty2);
    else
        vdist = INT_MAX;
    if (hdist < vdist)
    {
        hitx = nextx;
        hity = nexty;
    }
    else{
        hitx = nextx2;
        hity = nexty2;
    }
    draw_line(data, player->x, player->y, hitx, hity, 0xff000);
}

void rays(t_cub *data)
{
    float rangle;
    int    i;
    
    i = 0;
    rangle = data->player->rotationangle - (FOV_ANGLE / 2);
    while (i < NUM_RAYS)
    {
        data->rays[i].rayangle = normlize(rangle);
        if (data->rays[i].rayangle > 0 && data->rays[i].rayangle < PI)
        {
            data->rays[i].facingdown = 1;
            data->rays[i].facingup = 0;
        }
        else
        {
            data->rays[i].facingdown = 0;
            data->rays[i].facingup = 1;
        }
        if (data->rays[i].rayangle < 0.5 * PI || data->rays[i].rayangle > PI * 1.5)
        {
            data->rays[i].facingright = 1;
            data->rays[i].facingleft = 0;
        }
        else   {
            data->rays[i].facingright = 0;
            data->rays[i].facingleft = 1;
        }
        data->rays[i].columnid = i;
        // if (i == NUM_RAYS / 2)
        cast(data, data->player, data->rays[i]);
        rangle += FOV_ANGLE / NUM_RAYS;
        i++;
    }
}
int key2(int key, t_cub *data)
{
    if (key == 123)
        data->player->turndirection = 0;
    if (key == 124)
        data->player->turndirection = 0;
    if (key == 1)
         data->player->walkdirection = 0;
   if (key == 13)
        data->player->walkdirection = 0;
    return (0);
}

int key(int key, t_cub *data)
{  
    if (key == 1)
        data->player->walkdirection = -1;
   if (key == 13)
        data->player->walkdirection = +1;
    if (key == 123)
        data->player->turndirection = -1;
   if (key == 124)
        data->player->turndirection = +1;
    if (key == 53)
        exit (0);
    return(0);
}
void    get_images(t_cub *data)
{ 
    data->ground = mlx_xpm_file_to_image(data->init, "assets/ground.xpm", &data->x, &data->y);
    data->wall = mlx_xpm_file_to_image(data->init, "assets/wall.xpm", &data->x, &data->y);
    data->player->player = mlx_xpm_file_to_image(data->init, "assets/player.xpm", &data->x, &data->y);
}

void    draw_player(t_cub *data)
{
    mlx_put_image_to_window(data->init, data->win, data->player->player, data->player->x, data->player->y);
}

void    player_init(t_cub *data)
{
    data->player->x = WINDOW_WIDTH / 2;
    data->player->y = WINDOW_HEIGHT / 2;
    data->player->radius = 3.0;
    data->player->turndirection = 0; // +1 if left -1 for right
    data->player->walkdirection = 0; // +1 if up -1 for down
    data->player->rotationangle = PI / 2;
    data->player->movespeed = 3.0;
    data->player->rotationspeed = 3 * (PI / 180);
}

int    draw_map(t_cub *data)
{
    int y;
    int x;
    float newx;
    float newy;

    y = -1;
    while(data->map[++y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '1')
                mlx_put_image_to_window(data->init, data->win, data->wall, x * TILE_SIZE, y * TILE_SIZE);
            else
                mlx_put_image_to_window(data->init, data->win, data->ground, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
    }
    data->player->rotationangle += data->player->turndirection * data->player->rotationspeed;
    data->player->movestep = data->player->movespeed * data->player->walkdirection;
    newx = data->player->x + cos(data->player->rotationangle) * data->player->movestep;
    newy = data->player->y + sin(data->player->rotationangle) * data->player->movestep;
    if (data->map[(int)floor(newy / TILE_SIZE)][(int)floor(newx / TILE_SIZE)] != '1')
    {
        data->player->x = newx;
        data->player->y = newy;
    }
    rays(data);
    // draw_line(data,(float)data->player->x, (float)data->player->y, data->player->x + cos(data->player->rotationangle) * 30,  data->player->y + sin(data->player->rotationangle) * 30,  0x81FB59);
    draw_player(data);
    return (0);
}

void    fill_map(t_cub *data, int fd)
{
    int i;

    i = 0;
    data->map = malloc(sizeof(char *) * 15);
    data->map[14] = NULL;
    while (i < 15)
        data->map[i++] = get_next_line(fd);
}

int main()
{
    t_cub *data;
    int fd;
    
    data = malloc(sizeof(t_cub));
    data->player = malloc(sizeof(t_player));
    data->rays = malloc(sizeof(t_rays) * NUM_RAYS);
    fd = open("map.txt", O_RDONLY);
    if(!fd)
        return(printf("map not found \n"), 1);
    fill_map(data, fd);
    data->init = mlx_init();
    data->win = mlx_new_window(data->init, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    get_images(data);
    player_init(data);
    draw_map(data);
    mlx_hook(data->win, 2, 0, &key, data);
    mlx_hook(data->win, 3, 0, &key2, data);
    mlx_loop_hook(data->init, &draw_map, data);
    mlx_loop(data->init);
}