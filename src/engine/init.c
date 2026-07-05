/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 02:24:31 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/04 11:15:52 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_player_dir(t_game *game)
{
	if (game->player.orientation == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}	
	else if (game->player.orientation == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
	else if (game->player.orientation == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
	else if (game->player.orientation == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
	game->player.plane.x = -game->player.dir.y * 0.66;
	game->player.plane.y = game->player.dir.x * 0.66;
}

static int	init_textures(t_game *game, t_file *file)
{
	game->tex.no = mlx_load_png(file->texture->no);
	game->tex.so = mlx_load_png(file->texture->so);
	game->tex.we = mlx_load_png(file->texture->we);
	game->tex.ea = mlx_load_png(file->texture->ea);
	if (!game->tex.no || !game->tex.so || !game->tex.we
		|| !game->tex.ea)
		return (0);
	return (1);
}

int	init_game(t_game *game, t_file *file)
{
	game->floor = file->color_floor;
	game->ceiling = file->color_ceiling;
	game->map.grid = file->map;
	game->map.rows = file->total_row;
	game->map.cols = file->total_col;
	game->player.pos.x = file->player_col + 0.5;
	game->player.pos.y = file->player_row + 0.5;
	game->player.orientation = file->player_view;
	set_player_dir(game);
	if (!init_textures(game, file))
		return (1);
	return (0);
}

int	init_win(t_game *game)
{
	game->mlx = mlx_init(W_WIDTH, W_HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (1);
	}
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (1);
	}
	return (0);
}
