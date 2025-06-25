/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:17:03 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:31:50 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stddef.h>

size_t	apply_fog(size_t color, float distance, float max_distance)
{
	float	fog_intensity;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	fog_intensity = distance / max_distance;
	if (fog_intensity > 1.0f)
		fog_intensity = 1.0f;
	if (fog_intensity < 0.0f)
		fog_intensity = 0.0f;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	r = r * (1.0f - fog_intensity) + 0x30 * fog_intensity;
	g = g * (1.0f - fog_intensity) + 0x30 * fog_intensity;
	b = b * (1.0f - fog_intensity) + 0x30 * fog_intensity;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static void	sub_fnc_bg_fog(float horizon, int i, size_t bg_top, size_t bg_down)
{
	size_t	color;
	int		j;
	float	max_depth;
	float	depth;
	float	fog_intensity;

	max_depth = HEIGHT / 2.0f;
	depth = fabsf(i - horizon);
	fog_intensity = depth / max_depth;
	if (fog_intensity > 1.0f)
		fog_intensity = 1.0f;
	if (i < horizon)
		color = apply_fog(bg_top, 80 - (fog_intensity * 80), 80);
	else
		color = apply_fog(bg_down, 80 - (fog_intensity * 80), 80);
	j = 0;
	while (j < WIDTH)
		ft_texture(get_game()->game_t, j++, i, color);
}

static void	put_bg_fog(t_game *game, size_t bg_top, size_t bg_down)
{
	int		i;
	float	horizon;

	i = -1;
	horizon = HEIGHT / 2.0f + game->player.dir_y;
	while (++i < HEIGHT + 600)
		sub_fnc_bg_fog(horizon, i, bg_top, bg_down);
}

static void	put_bg(t_game *game, size_t bg_top, size_t bg_down)
{
	int		i;
	int		j;
	size_t	color;

	i = 0;
	color = bg_top;
	while (i < HEIGHT + 600)
	{
		if (i >= (HEIGHT / 2.0f) + game->player.dir_y)
			color = bg_down;
		j = 0;
		while (j < WIDTH)
		{
			ft_texture(game->game_t, j, i, color);
			j++;
		}
		i++;
	}
}

void	set_background(t_game *game)
{
	if (game->fog)
		put_bg_fog(game, game->text.c_color.rgb_hex,
			game->text.f_color.rgb_hex);
	else
		put_bg(game, game->text.c_color.rgb_hex, game->text.f_color.rgb_hex);
}
