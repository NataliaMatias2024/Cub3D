/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_raycast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 02:27:47 by mkitano           #+#    #+#             */
/*   Updated: 2026/06/30 03:06:24 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	calc_side_dis(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.step.x = -1;
		game->ray.side_dis.x = (game->player.pos.x
				- game->ray.map.x) * game->ray.delta_dis.x;
	}
	else
	{
		game->ray.step.x = 1;
		game->ray.side_dis.x = (game->ray.map.x + 1.0 - game->player.pos.x)
			* game->ray.delta_dis.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.step.y = -1;
		game->ray.side_dis.y = (game->player.pos.y
				- game->ray.map.y) * game->ray.delta_dis.y;
	}
	else
	{
		game->ray.step.y = 1;
		game->ray.side_dis.y = (game->ray.map.y + 1.0 - game->player.pos.y)
			* game->ray.delta_dis.y;
	}
}

void	setup_ray(t_game *game, int col)
{
	double	camera_x;

	camera_x = 2 * col / (double)game->mlx->width - 1;
	game->ray.dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	game->ray.dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	game->ray.map.x = (int)game->player.pos.x;
	game->ray.map.y = (int)game->player.pos.y;
	if (game->ray.dir.x == 0)
		game->ray.delta_dis.x = 1e30;
	else
		game->ray.delta_dis.x = fabs(1 / game->ray.dir.x);
	if (game->ray.dir.y == 0)
		game->ray.delta_dis.y = 1e30;
	else
		game->ray.delta_dis.y = fabs(1 / game->ray.dir.y);
	calc_side_dis(game);
}

void	perform_dda(t_game *game)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (game->ray.side_dis.x < game->ray.side_dis.y)
		{
			game->ray.side_dis.x += game->ray.delta_dis.x;
			game->ray.map.x += game->ray.step.x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dis.y += game->ray.delta_dis.y;
			game->ray.map.y += game->ray.step.y;
			game->ray.side = 1;
		}
		if (game->map.grid[(game->ray.map.y)][(game->ray.map.x)] == '1')
			hit = true;
	}
}

void	calc_perp_wall_dis(t_game *game)
{
	if (game->ray.side == 0)
	{
		game->ray.perp_dis = game->ray.side_dis.x - game->ray.delta_dis.x;
		game->ray.wall_x = game->player.pos.y
			+ game->ray.perp_dis * game->ray.dir.y;
	}
	else
	{
		game->ray.perp_dis = game->ray.side_dis.y - game->ray.delta_dis.y;
		game->ray.wall_x = game->player.pos.x
			+ game->ray.perp_dis * game->ray.dir.x;
	}
	if (game->ray.perp_dis < 1e-6)
		game->ray.perp_dis = 1e-6;
	game->ray.wall_x -= floor(game->ray.wall_x);
}
