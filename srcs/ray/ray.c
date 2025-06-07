/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:20:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/08 02:18:32 by knakto           ###   ########.fr       */
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
	t_vec2	cur;
	t_vec2	temp;
	int		r;
	t_tile	**map;
	float	scale;

	r = 0;
	map = get_game()->map.map;
	scale = get_game()->scale;
	cur.x = x;
	cur.y = y;
	while (r <= 5 * scale)
	// while (r >= 0)
	{
		temp.x = cur.x;
		temp.y = cur.y;
		cur.x = x + r * cos(rad);
		cur.y = y + r * sin(rad);
		if (map[(int)(cur.y / scale)][(int)(temp.x / scale)].type == WALL \
&& map[(int)(temp.y / scale)][(int)(cur.x / scale)].type == WALL)
			return (temp);
		if (map[(int)(cur.y / scale)][(int)(cur.x / scale)].type == WALL)
			return (cur);
		r++;
	}
	return (cur);
}

void	putray(mlx_texture_t *text)
{
	t_vec2		hit;
	t_player	player;
	t_player	minimap;
	float		rad;
	float		i;

	player = get_game()->player;
	minimap = get_game()->minimap;
	rad = player.dir * PI / 180;
	hit = find_hit(rad + 0.4, player.x, player.y);
	bresenham(text, (t_point){0x000000, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0x000000, hit.x + minimap.x, hit.y + minimap.y, 0});
	hit = find_hit(rad - 0.4, player.x, player.y);
	bresenham(text, (t_point){0x000000, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0x000000, hit.x + minimap.x, hit.y + minimap.y, 0});
	printf("->>%f\n", distance(player.x, player.y, hit.x, hit.y));
	i = -0.39;
	while (i < 0.39)
	{
		hit = find_hit(rad + i, player.x, player.y);
		// if ((int)(hit.x) % get_game()->scale == 0 && (int)(hit.y) % get_game()->scale == 0)
		// 	bresenham(text, (t_point){0xFF0000, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0xFF0000 , hit.x + minimap.x, hit.y + minimap.y, 0});
		// else
			bresenham(text, (t_point){0xAAAADD, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0xAAAADD, hit.x + minimap.x, hit.y + minimap.y, 0});
		i += 0.001;
	}
}
