/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 18:40:12 by izelensk          #+#    #+#             */
/*   Updated: 2017/05/24 18:40:17 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include "convert_xpm_hex.h"
# include <math.h>
# define PI 3.14159265

# define XSIZE 1000
# define YSIZE 600

# define XC (XSIZE / 2)
# define YC (YSIZE / 2)
# define COSN(angle) cos(angle * PI / 180)
# define SINS(angle) sin(angle * PI / 180)
# define POS(x, y) (x * 4 + y * data->size_line)

# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_ALEFT 123
# define KEY_ARIGHT 124
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_SHIFT 257

# define D data

# define MAPSIZE 24
# define TEXCOUNT 13
# define TEXCOUNTW 4
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define SPRITECOUNT 11

typedef	struct	s_sprite
{
	double			x;
	double			y;
	int				texture;
	int				killed;
}				t_sprite;

typedef	struct	s_hook
{
	int			left;
	int			right;
	int			up;
	int			down;
}				t_hook;

typedef	struct	s_data
{
	t_hook		hooks;
	t_sprite	sprites[SPRITECOUNT];
	double		zbuffer[XSIZE];
	double		s_dist[SPRITECOUNT];
	int			world_map[24][24];
	int			*texture[TEXCOUNT];
	int			s_order[SPRITECOUNT];
	int			*texture_weapon[TEXCOUNTW];

	void		*mlx;
	void		*win;
	void		*img;
	char		*ptr;
	int			bpp;
	int			size_line;
	int			endian;

	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		mov_speed;
	double		rot_speed;
	double		camera_x;
	double		ray_pos_x;
	double		ray_pos_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	double		floor_x_wall;
	double		floor_y_wall;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	double		weight;
	double		cur_floor_x;
	double		cur_floor_y;
	double		sprite_x;
	double		sprite_y;
	double		transform_x;
	double		transform_y;
	double		inv_d;
	double		temp_d;
	int			x;
	int			y;
	int			check;
	int			map_n;
	int			indx;
	int			loop_x;
	int			loop_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			text_num;
	int			tex_x;
	int			tex_y;
	int			floor_tex_x;
	int			floor_tex_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
	int			color;
	int			d;
	int			i;
	int			k;
	int			temp_o;
	int			kill_count;
	int			dy;
	int			dx;
	int			fire_mode;
	int			fire_hit;
	int			weapon_num;
}				t_data;

int				w_exit(t_data *data);
void			w_loop(t_data *data);
void			loop_init(t_data *data);
void			loop_init_step(t_data *data);
void			w_loop_main(t_data *data);
void			loop_hit(t_data *data);
void			loop_walls(t_data *data);
void			loop_draw_walls(t_data *data);
void			loop_floor(t_data *data);
void			loop_draw_floor(t_data *data);
void			loop_s_init(t_data *data);
void			loop_s_draw(t_data *data);
void			loop_s_dist(t_data *data);
void			draw_weapon(t_data *data);
int				w_expose(t_data *data);
int				w_release(int key, t_data *data);
int				w_press(int key, t_data *data);
void			w_keys_rotate(t_data *data);
int				w_keys(t_data *data);
void			init_sprites(double x, double y, int texture, t_sprite *sprite);
void			assign_image(int x, int y, int color, t_data *data);
int				game_end(t_data *data);
void			win_message(t_data *data);
void			init_map_a(t_data *data);
void			init_map_b(t_data *data);
void			init_map_c(t_data *data);
void			init_textures(t_data *data);
void			data_init(t_data *data);

#endif
