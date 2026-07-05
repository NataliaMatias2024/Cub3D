/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 03:55:39 by mkitano           #+#    #+#             */
/*   Updated: 2026/07/04 11:16:52 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

uint32_t	convert_color(uint32_t color)
{
	return (((color & 0x000000FF) << 24)
		| ((color & 0x0000FF00) << 8)
		| ((color & 0x00FF0000) >> 8)
		| ((color & 0xFF000000) >> 24));
}

uint32_t	apply_wall_shading(uint32_t color)
{
	t_rgba	c;

	c.r = (((color >> 24) & 0xFF) * 3) >> 2;
	c.g = (((color >> 16) & 0xFF) * 3) >> 2;
	c.b = (((color >> 8) & 0xFF) * 3) >> 2;
	c.a = (color & 0xFF);
	return ((c.r << 24) | (c.g << 16) | (c.b << 8) | c.a);
}
