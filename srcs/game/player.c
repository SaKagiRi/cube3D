/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 04:36:29 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:04:44 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "map.h"

void	put_body(mlx_texture_t *text, t_player player, float rad, size_t color)
{
	float		padding;
	t_point		front;
	t_point		left;
	t_point		right;
	t_player	mini;

	padding = get_game()->player_size;
	mini = get_game()->minimap;
	front.color = color;
	front.outcode = 0;
	front.px = player.x + mini.x + padding * cos(rad);
	front.py = player.y + mini.y + padding * sin(rad);
	left.color = color;
	left.outcode = 0;
	left.px = player.x + mini.x + (padding / 2) * cos(rad - PI / 1.5);
	left.py = player.y + mini.y + (padding / 2) * sin(rad - PI / 1.5);
	right.color = color;
	right.outcode = 0;
	right.px = player.x + mini.x + (padding / 2) * cos(rad + PI / 1.5);
	right.py = player.y + mini.y + (padding / 2) * sin(rad + PI / 1.5);
	drawline(text, front, left);
	drawline(text, front, right);
	drawline(text, left, right);
}

void	put_player(mlx_texture_t *text, t_player player, size_t color)
{
	float		rad;

	rad = player.dir_x * PI / 180;
	put_body(text, player, rad, color);
	ft_texture(text, player.x + get_game()->minimap.x,
		player.y + get_game()->minimap.y, color);
}
