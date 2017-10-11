/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_data_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:05:25 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 17:05:27 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_map_a(t_data *data)
{
	data->y = -1;
	while (++data->y < MAPSIZE)
	{
		data->x = -1;
		while (++data->x < MAPSIZE)
		{
			data->world_map[data->y][data->x] = 0;
			if (data->x == 0 || data->y == 0 || data->x == 23 || data->y == 23)
				data->world_map[data->y][data->x] = 2;
			else if ((data->x == data->y || data->y == abs(data->x - 24))
				&& data->x % 12 != 0 && data->y % 12 != 0)
				data->world_map[data->y][data->x] = 3;
		}
	}
	init_sprites(1.5, 2.5, 11, &data->sprites[0]);
	init_sprites(22.5, 1.5, 11, &data->sprites[1]);
	init_sprites(12.5, 12.5, 11, &data->sprites[2]);
	init_sprites(1.5, 22.5, 11, &data->sprites[3]);
	init_sprites(22.5, 21.5, 11, &data->sprites[4]);
	init_sprites(2.5, 1.5, 11, &data->sprites[5]);
	init_sprites(22.5, 3.5, 11, &data->sprites[6]);
	init_sprites(21.5, 22.5, 11, &data->sprites[7]);
	init_sprites(3.5, 22.5, 11, &data->sprites[8]);
	init_sprites(15.5, 22.5, 11, &data->sprites[9]);
	init_sprites(21.5, 18.5, 11, &data->sprites[10]);
}

void	init_map_b(t_data *data)
{
	data->y = -1;
	while (++data->y < MAPSIZE)
	{
		data->x = -1;
		while (++data->x < MAPSIZE)
		{
			data->world_map[data->y][data->x] = 0;
			if (data->x == 0 || data->y == 0 || data->x == 23 || data->y == 23)
				data->world_map[data->y][data->x] = 4;
			else if ((data->x % 5 == 0 || data->y % 12 == 0)
				&& data->x % 4 != 0 && data->y % 8 != 0)
				data->world_map[data->y][data->x] = 5;
		}
	}
	init_sprites(1.5, 1.5, 11, &data->sprites[0]);
	init_sprites(1.5, 11.5, 11, &data->sprites[1]);
	init_sprites(1.5, 13.5, 11, &data->sprites[2]);
	init_sprites(1.5, 22.5, 11, &data->sprites[3]);
	init_sprites(4.5, 18.5, 11, &data->sprites[4]);
	init_sprites(4.5, 1.5, 11, &data->sprites[5]);
	init_sprites(4.5, 22.5, 11, &data->sprites[6]);
	init_sprites(9.5, 1.5, 11, &data->sprites[7]);
	init_sprites(9.5, 11.5, 11, &data->sprites[8]);
	init_sprites(9.5, 13.5, 11, &data->sprites[9]);
	init_sprites(9.5, 22.5, 11, &data->sprites[10]);
}

void	init_map_c(t_data *data)
{
	data->y = -1;
	while (++data->y < MAPSIZE)
	{
		data->x = -1;
		while (++data->x < MAPSIZE)
		{
			data->world_map[data->y][data->x] = 0;
			if (data->x == 0 || data->y == 0 || data->x == 23 || data->y == 23)
				data->world_map[data->y][data->x] = 6;
			else if (data->x % 2 != 0 && data->y % 2 != 0)
				data->world_map[data->y][data->x] = 7;
		}
	}
	init_sprites(1.5, 2.5, 9, &data->sprites[0]);
	init_sprites(1.5, 22.5, 9, &data->sprites[1]);
	init_sprites(3.5, 18.5, 9, &data->sprites[2]);
	init_sprites(6.5, 5.5, 9, &data->sprites[3]);
	init_sprites(7.5, 20.5, 9, &data->sprites[4]);
	init_sprites(8.5, 17.5, 9, &data->sprites[5]);
	init_sprites(12.5, 11.5, 9, &data->sprites[6]);
	init_sprites(16.5, 19.5, 9, &data->sprites[7]);
	init_sprites(16.5, 1.5, 9, &data->sprites[8]);
	init_sprites(18.5, 3.5, 9, &data->sprites[9]);
	init_sprites(22.5, 21.5, 9, &data->sprites[10]);
}

void	init_textures(t_data *data)
{
	convert_xpm_hex("res/brick_wall_2.xpm", &data->texture[0], 64);
	convert_xpm_hex("res/brick_wall_2.xpm", &data->texture[1], 64);
	convert_xpm_hex("res/brick_wall_2.xpm", &data->texture[2], 64);
	convert_xpm_hex("res/brick_wall_1.xpm", &data->texture[3], 64);
	convert_xpm_hex("res/brick_wall_1.xpm", &data->texture[4], 64);
	convert_xpm_hex("res/cat.xpm", &data->texture[5], 64);
	convert_xpm_hex("res/cat.xpm", &data->texture[6], 64);
	convert_xpm_hex("res/floor_01.xpm", &data->texture[7], 64);
	convert_xpm_hex("res/floor_02.xpm", &data->texture[8], 64);
	convert_xpm_hex("res/cat.xpm", &data->texture[9], 64);
	convert_xpm_hex("res/blood_splash.xpm", &data->texture[10], 64);
	convert_xpm_hex("res/enemy_1_64.xpm", &data->texture[11], 64);
	convert_xpm_hex("res/blood_1_64.xpm", &data->texture[12], 64);
	convert_xpm_hex("res/weapon_2.xpm", &data->texture_weapon[0], 256);
	convert_xpm_hex("res/weapon_2_fire.xpm", &data->texture_weapon[1], 256);
	convert_xpm_hex("res/weapon_256.xpm", &data->texture_weapon[2], 256);
	convert_xpm_hex("res/weapon_256_fire.xpm", &data->texture_weapon[3], 256);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, XSIZE, YSIZE, "wolf3d");
	data->img = mlx_new_image(data->mlx, XSIZE, YSIZE);
	data->ptr = mlx_get_data_addr(data->img, &(data->bpp),
	&(data->size_line), &(data->endian));
}

void	data_init(t_data *data)
{
	if (data->map_n == 1)
		init_map_a(data);
	if (data->map_n == 2)
		init_map_b(data);
	if (data->map_n == 3)
		init_map_c(data);
	data->pos_x = 2.5;
	data->pos_y = 3.5;
	data->dir_x = -1.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.66;
	data->rot_speed = 1.6;
	data->mov_speed = 0.05;
	data->check = 42;
	data->hooks.up = 0;
	data->hooks.down = 0;
	data->hooks.left = 0;
	data->hooks.right = 0;
	data->fire_mode = 0;
	data->weapon_num = 0;
	init_textures(data);
}
