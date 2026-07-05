/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:58:35 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/04 11:16:23 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	key_hook(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (key.key == MLX_KEY_M && key.action == MLX_PRESS)
	{
		game->mouse_enable = !game->mouse_enable;
		if (game->mouse_enable)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	}
	if (key.key == MLX_KEY_N && key.action == MLX_PRESS)
		game->mini.map_on = !game->mini.map_on;
}
