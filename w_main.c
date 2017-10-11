/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:07:55 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 17:07:57 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		w_exit(t_data *data)
{
	int i;

	i = 0;
	while (i < TEXCOUNT)
	{
		close(i + 3);
		free(data->texture[i]);
		if (i < TEXCOUNTW)
			free(data->texture_weapon[i]);
		i++;
	}
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	write(1, "Thx for attention\n", 18);
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data		data;

	data.map_n = 0;
	if (argc == 2)
	{
		if (argv[1][0] == '1' && argv[1][1] == '\0')
			data.map_n = 1;
		else if (argv[1][0] == '2' && argv[1][1] == '\0')
			data.map_n = 2;
		else if (argv[1][0] == '3' && argv[1][1] == '\0')
			data.map_n = 3;
		if (data.map_n)
		{
			if (data.check != 42)
				data_init(&data);
			w_loop(&data);
			mlx_expose_hook(data.win, &w_expose, &data);
			mlx_loop(data.mlx);
			return (0);
		}
	}
	write(1, "usage: ./wolf3d [1-3]\n", 22);
	return (0);
}
