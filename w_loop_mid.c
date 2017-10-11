/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_loop_mid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:06:32 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 17:06:33 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	loop_walls(t_data *data)
{
	data->line_height = (int)(YSIZE / data->perp_wall_dist);
	data->draw_start = (-data->line_height / 2) + (YSIZE / 2);
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = (data->line_height / 2) + (YSIZE / 2);
	if (data->draw_end >= YSIZE)
		data->draw_end = YSIZE - 1;
	data->text_num = data->world_map[data->map_x][data->map_y] - 1;
	if (data->side == 0)
		data->wall_x = data->ray_pos_y + data->perp_wall_dist
		* data->ray_dir_y;
	else
		data->wall_x = data->ray_pos_x + data->perp_wall_dist
		* data->ray_dir_x;
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (double)TEXWIDTH);
	if (data->side == 0 && data->ray_dir_x > 0)
		data->tex_x = TEXWIDTH - data->tex_x - 1;
	if (data->side == 1 && data->ray_dir_y < 0)
		data->tex_x = TEXWIDTH - data->tex_x - 1;
}

void	loop_draw_walls(t_data *data)
{
	int		d;
	int		y;
	int		color;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		d = y * 256 - YSIZE * 128 + data->line_height * 128;
		data->tex_y = ((d * TEXHEIGHT) / data->line_height) / 256;
		color = data->texture[data->text_num][TEXHEIGHT
		* data->tex_y + data->tex_x];
		if (data->side == 1)
			color = (color >> 1) & 0x7f7f7f;
		assign_image(data->loop_x, y, color, data);
		y++;
	}
}

void	loop_floor(t_data *data)
{
	if (data->side == 0 && data->ray_dir_x > 0)
	{
		data->floor_x_wall = data->map_x;
		data->floor_y_wall = data->map_y + data->wall_x;
	}
	else if (data->side == 0 && data->ray_dir_x < 0)
	{
		data->floor_x_wall = data->map_x + 1.0;
		data->floor_y_wall = data->map_y + data->wall_x;
	}
	else if (data->side == 1 && data->ray_dir_y > 0)
	{
		data->floor_x_wall = data->map_x + data->wall_x;
		data->floor_y_wall = data->map_y;
	}
	else
	{
		data->floor_x_wall = data->map_x + data->wall_x;
		data->floor_y_wall = data->map_y + 1.0;
	}
	data->dist_wall = data->perp_wall_dist;
	data->dist_player = 0.0;
	if (data->draw_end < 0)
		data->draw_end = YSIZE;
}

void	loop_draw_floor(t_data *data)
{
	int		color;

	data->loop_y = data->draw_end;
	while (data->loop_y < YSIZE)
	{
		data->current_dist = (double)YSIZE / (2.0 * data->loop_y - YSIZE);
		data->weight = (data->current_dist - data->dist_player)
		/ (data->dist_wall - data->dist_player);
		data->cur_floor_x = data->weight * data->floor_x_wall
		+ (1.0 - data->weight) * data->pos_x;
		data->cur_floor_y = data->weight * data->floor_y_wall
		+ (1.0 - data->weight) * data->pos_y;
		data->floor_tex_x = (int)(data->cur_floor_x * TEXWIDTH) % TEXWIDTH;
		data->floor_tex_y = (int)(data->cur_floor_y * TEXHEIGHT) % TEXHEIGHT;
		color = data->texture[8][TEXWIDTH * data->floor_tex_y
		+ data->floor_tex_x];
		color = (color >> 1) & 0x7f7f7f;
		assign_image(data->loop_x, data->loop_y, color, data);
		color = data->texture[7][TEXWIDTH * data->floor_tex_y
		+ data->floor_tex_x];
		assign_image(data->loop_x, YSIZE - data->loop_y, color, data);
		data->loop_y++;
	}
}
