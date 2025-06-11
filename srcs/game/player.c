/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 04:36:29 by knakto            #+#    #+#             */
/*   Updated: 2025/06/11 15:45:38 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	put_body(mlx_texture_t *text, t_player player, float rad, size_t color)
{
	float		padding;
	t_point		front;
	// t_point		left;
	// t_point		right;

	padding = get_game()->player_size;
	front.color = color;
	front.outcode = 0;
	front.px = player.x + padding * cos(rad);
	front.py = player.y + padding * sin(rad);
	// left.color = color;
	// left.outcode = 0;
	// left.px = player.x + (padding / 2) * cos(rad - PI / 1.5);
	// left.py = player.y + (padding / 2) * sin(rad - PI / 1.5);
	// right.color = color;
	// right.outcode = 0;
	// right.px = player.x + (padding / 2) * cos(rad + PI / 1.5);
	// right.py = player.y + (padding / 2) * sin(rad + PI / 1.5);
	// drawline(text, front, left);
	// drawline(text, front, right);
	// drawline(text, left, right);
	drawline(text, front, (t_point){color, player.x, player.y, 0});
}

void	put_player(mlx_texture_t *text, t_player player, size_t color)
{
	float		rad;

	player.x = (int)(MINI_WIDTH / 2);
	player.y = (int)(MINI_HEIGHT / 2);
	rad = player.dir * PI / 180;
	put_body(text, player, rad, color);
	ft_texture(text, player.x, player.y, 0x000000);
	ft_texture(text, player.x + 1, player.y, 0x000000);
	ft_texture(text, player.x - 1, player.y, 0x000000);
	ft_texture(text, player.x, player.y + 1, 0x000000);
	ft_texture(text, player.x, player.y - 1, 0x000000);
	// putray(text);
}
