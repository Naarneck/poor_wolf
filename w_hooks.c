/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:04:29 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 17:04:31 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		w_expose(t_data *data)
{
	mlx_key_hook(data->win, &w_release, data);
	mlx_hook(data->win, 2, 1L << 0, &w_press, data);
	mlx_hook(data->win, 17, 1L << 17, &w_exit, data);
	mlx_loop_hook(data->mlx, &w_keys, data);
	return (0);
}

int		w_release(int key, t_data *data)
{
	if (key == KEY_UP)
		data->hooks.up = 0;
	if (key == KEY_DOWN)
		data->hooks.down = 0;
	if (key == KEY_ALEFT || key == KEY_LEFT)
		data->hooks.left = 0;
	if (key == KEY_ARIGHT || key == KEY_RIGHT)
		data->hooks.right = 0;
	if (key == KEY_SPACE)
		data->fire_mode = 0;
	if (key == KEY_SHIFT)
		data->mov_speed = 0.05;
	if (key == KEY_ESC)
		w_exit(data);
	return (0);
}

int		w_press(int key, t_data *data)
{
	if (key == KEY_UP)
		data->hooks.up = 1;
	if (key == KEY_DOWN)
		data->hooks.down = 1;
	if (key == KEY_ALEFT || key == KEY_LEFT)
		data->hooks.left = 1;
	if (key == KEY_ARIGHT || key == KEY_RIGHT)
		data->hooks.right = 1;
	if (key == KEY_SPACE)
		data->fire_mode = 1;
	if (key == KEY_ONE)
		data->weapon_num = 0;
	if (key == KEY_TWO)
		data->weapon_num = 2;
	if (key == KEY_SHIFT)
		data->mov_speed = 0.1;
	return (0);
}

void	w_keys_rotate(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	int		r;

	r = 1;
	if (data->hooks.right)
		r = -1;
	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * COSN(data->rot_speed * r)
	- data->dir_y * SINS(data->rot_speed * r);
	data->dir_y = old_dir_x * SINS(data->rot_speed * r)
	+ data->dir_y * COSN(data->rot_speed * r);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * COSN(data->rot_speed * r)
	- data->plane_y * SINS(data->rot_speed * r);
	data->plane_y = old_plane_x * SINS(data->rot_speed * r)
	+ data->plane_y * COSN(data->rot_speed * r);
}

int		w_keys(t_data *data)
{
	if (data->hooks.up)
	{
		if (data->world_map[(int)(data->pos_x + data->dir_x
			* data->mov_speed)][(int)(data->pos_y)] == 0)
			data->pos_x += data->dir_x * data->mov_speed;
		if (data->world_map[(int)(data->pos_x)][(int)(data->pos_y
			+ data->dir_y * data->mov_speed)] == 0)
			data->pos_y += data->dir_y * data->mov_speed;
	}
	if (data->hooks.down)
	{
		if (data->world_map[(int)(data->pos_x - data->dir_x
			* data->mov_speed)][(int)(data->pos_y)] == 0)
			data->pos_x -= data->dir_x * data->mov_speed;
		if (data->world_map[(int)(data->pos_x)][(int)(data->pos_y
			- data->dir_y * data->mov_speed)] == 0)
			data->pos_y -= data->dir_y * data->mov_speed;
	}
	if (data->hooks.left || data->hooks.right)
		w_keys_rotate(data);
	w_loop(data);
	return (0);
}
