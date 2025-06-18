/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:27:35 by knakto            #+#    #+#             */
/*   Updated: 2025/06/19 03:13:43 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include <stddef.h>
#include <stdlib.h>

int	ft_texture(mlx_texture_t *texture, float x, float y, size_t rgb)
{
	size_t	position;

	if (x < 0 || y < 0)
		return (-1);
	if (x >= texture->width || y >= texture->height)
		return (-1);
	position = ((int32_t)y * texture->width * 4) + ((int32_t)x * 4);
	texture->pixels[position] = rgb >> 24 & 0xFF;
	texture->pixels[position + 1] = rgb >> 16 & 0xFF;
	texture->pixels[position + 2] = rgb >> 8 & 0xFF;
	texture->pixels[position + 3] = 0xFF;
	return (0);
}

void	fill_background(mlx_texture_t *texture, size_t bg_color)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			ft_texture(texture, x, y, bg_color);
			x++;
		}
		y++;
	}
}

mlx_texture_t	*new_texture(size_t w, size_t h, size_t bg_color)
{
	mlx_texture_t	*texture;
	uint8_t			*pixels;

	texture = malloc(sizeof(mlx_texture_t));
	pixels = malloc(sizeof(uint8_t) * w * h * 4);
	if (!texture || !pixels)
		return (NULL);
	texture->width = w;
	texture->height = h;
	texture->bytes_per_pixel = 4;
	texture->pixels = pixels;
	fill_background(texture, bg_color);
	return (texture);
}

int	ft_texture_color(mlx_texture_t *texture, size_t x, size_t y, size_t *color)
{
	size_t	position;
	size_t	r;
	size_t	g;
	size_t	b;
	size_t	a;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (-1);
	position = ((int32_t)y * texture->width * 4) + ((int32_t)x * 4);
	r = texture->pixels[position + 0] & 0xFF;
	g = texture->pixels[position + 1] & 0xFF;
	b = texture->pixels[position + 2] & 0xFF;
	a = texture->pixels[position + 3] & 0xFF;
	*color = (r << 24 | g << 16 | b << 8 | a);
	return (0);
}
