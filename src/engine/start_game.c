/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 00:27:52 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/03 05:20:50 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	key_move(game);
	handle_rotate(game);
	raycast(game);
	minimap(game);
}
