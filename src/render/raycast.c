/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 21:48:49 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/01 03:40:24 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	raycast(t_game *game)
{
	int	col;

	render_bg(game);
	col = -1;
	while (++col < W_WIDTH)
	{
		setup_ray(game, col);
		perform_dda(game);
		calc_perp_wall_dis(game);
		render_col(game, col);
	}
}
