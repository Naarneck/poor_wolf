/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:24:02 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 17:24:04 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_sprites(double x, double y, int texture, t_sprite *sprite)
{
	sprite->x = y;
	sprite->y = x;
	sprite->texture = texture;
	sprite->killed = 0;
}

void	assign_image(int x, int y, int color, t_data *data)
{
	data->indx = POS(x, y);
	data->ptr[data->indx] = color & 0x0000ff;
	data->ptr[data->indx + 1] = (color >> 8) & 0x0000ff;
	data->ptr[data->indx + 2] = color >> 16;
}

int		game_end(t_data *data)
{
	data->k = 0;
	data->kill_count = 0;
	while (data->k < SPRITECOUNT)
	{
		if (data->sprites[data->k].killed == 1)
			data->kill_count++;
		data->k++;
	}
	if (data->kill_count == SPRITECOUNT)
		return (1);
	return (0);
}

void	win_message(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, XSIZE, YSIZE);
	data->y = 0;
	while (data->y < YSIZE)
	{
		data->x = 0;
		while (data->x < XSIZE)
		{
			assign_image(data->x, data->y, 0xf78036, data);
			data->x++;
		}
		data->y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_string_put(data->mlx, data->win, XC - 10, YC - 10, 0, "YOU WIN!");
}
