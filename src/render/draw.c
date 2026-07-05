/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 21:49:25 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/01 17:24:04 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	calc_wall(t_game *game)
{
	game->ray.line_height = ((int)game->mlx->height / game->ray.perp_dis);
	game->ray.draw_start = game->mlx->height / 2 - game->ray.line_height / 2;
	game->ray.offset_y = 0;
	if (game->ray.draw_start < 0)
	{
		game->ray.offset_y = -game->ray.draw_start;
		game->ray.draw_start = 0;
	}
	game->ray.draw_end = game->mlx->height / 2 + game->ray.line_height / 2;
	if (game->ray.draw_end >= game->mlx->height)
		game->ray.draw_end = game->mlx->height - 1;
}

static mlx_texture_t	*get_wall_tex(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir.x > 0)
			return (game->tex.ea);
		return (game->tex.we);
	}
	if (game->ray.dir.y > 0)
		return (game->tex.so);
	return (game->tex.no);
}

static int	cal_tex_x(t_game *game, mlx_texture_t *tex)
{
	int	tex_x;

	tex_x = (int)(game->ray.wall_x * tex->width);
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	if (game->ray.side == 0 && game->ray.dir.x > 0)
		tex_x = tex->width - tex_x - 1;
	if (game->ray.side == 1 && game->ray.dir.y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	render_wall(t_game *game, mlx_texture_t *tex, int col, int y)
{
	double		tex_pos;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	tex_x = cal_tex_x(game, tex);
	tex_pos = (double)(y - game->ray.draw_start
			+ game->ray.offset_y) / game->ray.line_height;
	if (tex_pos < 0)
		tex_pos = 0;
	if (tex_pos > 1)
		tex_pos = 1;
	tex_y = (int)(tex_pos * tex->height);
	if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
	color = convert_color(((uint32_t *)tex->pixels)[tex_y * tex->width
			+ tex_x]);
	if (game->ray.side == 1)
		color = apply_wall_shading(color);
	mlx_put_pixel(game->img, col, y, color);
}

void	render_col(t_game *game, int col)
{
	int	y;

	calc_wall(game);
	y = game->ray.draw_start;
	while (y <= game->ray.draw_end)
	{
		render_wall(game, get_wall_tex(game), col, y);
		y++;
	}
}
