/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:21:15 by mkitano           #+#    #+#             */
/*   Updated: 2026/06/15 17:21:15 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "parser.h"

# define W_WIDTH 1200
# define W_HEIGHT 800

# define MINI_TILE_SIZE 12
# define MINI_RAD 5
# define PLAYER_SIZE 12

typedef struct s_rgba
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_rgba;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_ivec
{
	int	x;
	int	y;
}	t_ivec;

typedef struct s_minimap
{
	t_ivec		player;
	t_ivec		start;
	t_ivec		center;
	int			map_on;
}	t_minimap;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	char	orientation;
	double	mov_speed;
	double	rot_speed;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	side_dis;
	t_vec	delta_dis;
	t_ivec	map;
	t_ivec	step;
	int		side;
	double	perp_dis;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		offset_y;
}	t_ray;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_textures;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_textures	tex;
	uint32_t	floor;
	uint32_t	ceiling;
	t_map		map;
	t_player	player;
	t_ray		ray;
	int			mouse_enable;
	t_minimap	mini;
}	t_game;

int			init_game(t_game *game, t_file *file);
int			init_win(t_game *game);

void		key_move(t_game *game);

void		handle_rotate(t_game *game);
void		mouse_rotate(t_game *game);
void		key_hook(mlx_key_data_t key, void *param);

void		game_loop(void *param);

void		setup_ray(t_game *game, int col);
void		calc_perp_wall_dis(t_game *game);
void		perform_dda(t_game *game);

void		render_col(t_game *game, int col);

uint32_t	convert_color(uint32_t color);
uint32_t	apply_wall_shading(uint32_t color);

uint32_t	reverse_bytes(uint32_t c);
void		render_bg(t_game *game);
void		raycast(t_game *game);

void		draw_minimap(t_game *game);
void		draw_player(t_game *game);
void		init_minimap(t_game *game);
void		minimap(t_game *game);

void		clean_game(t_game *game, t_parser *parser);

#endif