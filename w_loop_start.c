/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_loop_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:06:18 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 17:06:20 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	loop_init_step(t_data *data)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = data->delta_dist_x
		* (data->ray_pos_x - data->map_x);
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = data->delta_dist_x
		* (data->map_x + 1.0 - data->ray_pos_x);
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = data->delta_dist_y *
		(data->ray_pos_y - data->map_y);
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = data->delta_dist_y
		* (data->map_y + 1.0 - data->ray_pos_y);
	}
}

void	loop_init(t_data *data)
{
	data->camera_x = 2 * data->loop_x / (double)XSIZE - 1;
	data->ray_pos_x = data->pos_x;
	data->ray_pos_y = data->pos_y;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	data->map_x = (int)data->ray_pos_x;
	data->map_y = (int)data->ray_pos_y;
	data->delta_dist_x = sqrt(1 + (data->ray_dir_y * data->ray_dir_y)
	/ (data->ray_dir_x * data->ray_dir_x));
	data->delta_dist_y = sqrt(1 + (data->ray_dir_x * data->ray_dir_x)
	/ (data->ray_dir_y * data->ray_dir_y));
	data->hit = 0;
	data->side = 0;
	loop_init_step(data);
}

void	loop_hit(t_data *data)
{
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (data->world_map[data->map_x][data->map_y] > 0)
			data->hit = 1;
	}
	if (data->side == 0)
		data->perp_wall_dist = (data->map_x - data->ray_pos_x
		+ (1 - data->step_x) / 2) / data->ray_dir_x;
	else
		data->perp_wall_dist = (data->map_y - data->ray_pos_y
		+ (1 - data->step_y) / 2) / data->ray_dir_y;
}

void	w_loop_main(t_data *data)
{
	loop_init(data);
	loop_hit(data);
	loop_walls(data);
	loop_draw_walls(data);
	data->zbuffer[data->loop_x] = data->perp_wall_dist;
	loop_floor(data);
	loop_draw_floor(data);
}

void	w_loop(t_data *data)
{
	if (game_end(data))
		win_message(data);
	else
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, XSIZE, YSIZE);
		data->loop_x = 0;
		while (data->loop_x < XSIZE)
		{
			w_loop_main(data);
			data->loop_x++;
		}
		loop_s_dist(data);
		data->i = 0;
		while (data->i < SPRITECOUNT)
		{
			loop_s_init(data);
			loop_s_draw(data);
			data->i++;
		}
		draw_weapon(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
}
