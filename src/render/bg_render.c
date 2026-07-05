/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 03:30:35 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/03 12:54:01 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

uint32_t	reverse_bytes(uint32_t c)
{
	return (((c & 0xFF000000) >> 24)
		| ((c & 0x00FF0000) >> 8)
		| ((c & 0x0000FF00) << 8)
		| ((c & 0x000000FF) << 24));
}

static void	fill_block(uint64_t *buffer, uint64_t pattern, uint64_t size)
{
	uint64_t	i;

	i = 0;
	while ((i + 8) <= size)
	{
		buffer[i] = pattern;
		buffer[i + 1] = pattern;
		buffer[i + 2] = pattern;
		buffer[i + 3] = pattern;
		buffer[i + 4] = pattern;
		buffer[i + 5] = pattern;
		buffer[i + 6] = pattern;
		buffer[i + 7] = pattern;
		i += 8;
	}
	while (i < size)
		buffer[i++] = pattern;
}

static uint64_t	make_pattern(uint32_t color)
{
	uint64_t	pattern;
	uint32_t	swap_c;

	swap_c = reverse_bytes(color);
	pattern = ((uint64_t)swap_c << 32) | swap_c;
	return (pattern);
}

void	render_bg(t_game *game)
{
	uint64_t	*buffer;
	uint64_t	ceiling_pattern;
	uint64_t	floor_pattern;
	uint64_t	total_qwords;
	uint64_t	half_qwords;

	buffer = (uint64_t *)game->img->pixels;
	ceiling_pattern = make_pattern(game->ceiling);
	floor_pattern = make_pattern(game->floor);
	total_qwords = (game->img->width * game->img->height) >> 1;
	half_qwords = total_qwords >> 1;
	fill_block(buffer, ceiling_pattern, half_qwords);
	fill_block(buffer + half_qwords, floor_pattern, total_qwords - half_qwords);
}
