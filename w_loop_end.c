/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_loop_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:06:42 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 17:06:43 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	loop_s_init(t_data *data)
{
	data->sprite_x = data->sprites[data->s_order[data->i]].x - data->pos_x;
	data->sprite_y = data->sprites[data->s_order[data->i]].y - data->pos_y;
	data->inv_d = 1.0 / ((data->plane_x * data->dir_y)
	- (data->dir_x * data->plane_y));
	data->transform_x = data->inv_d * (data->dir_y * data->sprite_x
	- data->dir_x * data->sprite_y);
	data->transform_y = data->inv_d * (-data->plane_y * data->sprite_x
	+ data->plane_x * data->sprite_y);
	data->sprite_screen_x = (int)((XSIZE / 2) * (1 + (data->transform_x
	/ data->transform_y)));
	data->sprite_height = abs((int)(YSIZE / (data->transform_y)));
	data->draw_start_y = -data->sprite_height / 2 + YSIZE / 2;
	if (data->draw_start_y < 0)
		data->draw_start_y = 0;
	data->draw_end_y = data->sprite_height / 2 + YSIZE / 2;
	if (data->draw_end_y >= YSIZE)
		data->draw_end_y = YSIZE - 1;
	data->sprite_width = abs((int)(YSIZE / (data->transform_y)));
	data->draw_start_x = -data->sprite_width / 2 + data->sprite_screen_x;
	if (data->draw_start_x < 0)
		data->draw_start_x = 0;
	data->draw_end_x = data->sprite_width / 2 + data->sprite_screen_x;
	if (data->draw_end_x >= XSIZE)
		data->draw_end_x = XSIZE - 1;
}

void	loop_s_draw(t_data *data)
{
	data->loop_x = data->draw_start_x;
	while (data->loop_x < data->draw_end_x)
	{
		data->tex_x = (int)(256 * (data->loop_x - (-data->sprite_width
		/ 2 + data->sprite_screen_x)) * TEXWIDTH / data->sprite_width) / 256;
		if (data->transform_y > 0 && data->loop_x > 0 && data->loop_x < XSIZE
		&& data->transform_y < data->zbuffer[data->loop_x])
		{
			data->loop_y = data->draw_start_y;
			while (data->loop_y < data->draw_end_y)
			{
				data->d = (data->loop_y) * 256 - (YSIZE * 128)
				+ (data->sprite_height * 128);
				data->tex_y = ((D->d * TEXHEIGHT) / D->sprite_height) / 256;
				if (data->fire_mode && data->loop_x == XC)
					data->sprites[data->i].killed = 1;
				D->color = D->texture[D->sprites[D->s_order[D->i]].texture
				+ D->sprites[D->i].killed][64 * D->tex_y + D->tex_x];
				if (data->color != 0x00)
					assign_image(D->loop_x, D->loop_y, D->color, data);
				data->loop_y++;
			}
		}
		data->loop_x++;
	}
}

void	loop_s_dist(t_data *data)
{
	data->i = 0;
	while (data->i < SPRITECOUNT)
	{
		data->s_order[data->i] = data->i;
		data->s_dist[data->i] = (((data->pos_x - data->sprites[data->i].x)
		* (data->pos_x - data->sprites[data->i].x)) +
		((data->pos_y - data->sprites[data->i].y) +
		(data->pos_y - data->sprites[data->i].y)));
		data->i++;
	}
}

void	draw_weapon(t_data *data)
{
	double	n;

	n = (double)(XSIZE) / (256.0 * 2.0);
	data->dy = (int)((double)(YSIZE) - (256 * n));
	data->dx = (int)((double)(XSIZE) - (256 * n));
	data->y = 0;
	while (data->y < (int)(256 * n))
	{
		data->x = 0;
		while (data->x < (int)(256 * n))
		{
			data->tex_x = (int)(data->x / n);
			data->tex_y = (int)(data->y / n);
			data->color = data->texture_weapon[data->fire_mode
			+ data->weapon_num][256 * data->tex_y + data->tex_x];
			if (data->color != 0x00)
			{
				assign_image(data->x + data->dx, data->y
				+ data->dy, data->color, data);
			}
			data->x++;
		}
		data->y++;
	}
}
