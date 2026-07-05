/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 11:18:26 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/04 11:18:46 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	minimap(t_game *game)
{
	if (game->mini.map_on)
	{
		init_minimap(game);
		draw_minimap(game);
		draw_player(game);
	}
}
