/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:20:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/07 16:48:50 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "drawline.h"
#include "cube.h"
#include "game.h"
#include "ray.h"
#include <math.h>

double	distance(float px, float py, float hx, float hy)
{
	return (sqrt(pow(hx - px, 2) + pow(hy - py, 2)));
}

t_vec2	find_hit(float rad, float x, float y)
{
	double	px;
	double	py;
	int		r;
	t_tile	**map;
	float	scale;

	r = 0;
	map = get_game()->map.map;
	scale = get_game()->scale;
	while (r >= 0)
	{
		px = x + r * cos(rad);
		py = y + r * sin(rad);
		if (map[(int)(py / scale)][(int)(px / scale)].type == WALL)
			return ((t_vec2){px, py});
		r++;
	}
	return ((t_vec2){0, 0});
}

void	putray(mlx_texture_t *text)
{
	t_vec2		hit;
	t_player	player;
	float		rad;

	player = get_game()->player;
	rad = player.dir * PI / 180;
	hit = find_hit(rad, player.x, player.y);
	printf("->>%f\n", distance(player.x, player.y, hit.x, hit.y));
	bresenham(text, (t_point){0xFF0000, player.x, player.y, 0}, (t_point){0xFF0000, hit.x, hit.y, 0});
	hit = find_hit(rad + 0.5, player.x, player.y);
	printf("->>%f\n", distance(player.x, player.y, hit.x, hit.y));
	bresenham(text, (t_point){0x000000, player.x, player.y, 0}, (t_point){0x000000, hit.x, hit.y, 0});
	hit = find_hit(rad - 0.5, player.x, player.y);
	printf("->>%f\n", distance(player.x, player.y, hit.x, hit.y));
	bresenham(text, (t_point){0x000000, player.x, player.y, 0}, (t_point){0x000000, hit.x, hit.y, 0});
}
