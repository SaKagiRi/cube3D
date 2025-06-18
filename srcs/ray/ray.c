/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:20:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/16 17:58:47 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "../../include/cube.h"
#include "drawline.h"
#include "cube.h"
#include "game.h"
#include <math.h>
#include <stdlib.h>

float	distance(float px, float py, t_vec2 hit, float dir)
{
	float	dis;
	float	rad;

	float dx = hit.x - px;
	float dy = hit.y - py;
	dis = sqrt(dx * dx + dy * dy);
	rad = dir * PI / 180;
	return (dis * cos(rad));
}

int		set_side(float hx, float hy, float rad)
{
	int		scale;

	scale = SCALE;
	// if (((int)hx % scale == 0 || (int)hx % scale == scale - 1) && ((int)hy % scale == 0 || (int)hy % scale == scale - 1))
	// {
	// 	rad = rad * 180 / M_PI;
	// 	if (rad < 0)
	// 		rad += 360;
	// 	if (rad >= 45 && rad < 135)
	// 		return (NORTH);
	// 	else if (rad >= 135 && rad < 225)
	// 		return (WEST);
	// 	else if (rad >= 225 && rad < 315)
	// 		return (SOUTH);
	// 	else
	// 		return (EAST);
	// }
	(void)rad;
	if ((int)hx % scale == 0)
		return (WEST);
	else if ((int)hx % scale == scale - 1)
		return (EAST);
	else if ((int)hy % scale == 0)
		return (NORTH);
	else if ((int)hy % scale == scale - 1)
		return (SOUTH);
	return (-1);
}

t_dist	find_hit(float ray_angle, float x, float y)
{
	t_vec2	cur;
	t_vec2	temp;
	float	r;
	t_tile	**map;
	int		scale;
	float	rad;
	int		side;

	r = 0;
	map = get_game()->map.map;
	scale = SCALE;
	rad = ray_angle * PI / 180;
	cur.x = x;
	cur.y = y;
	side = 0;
	// while (r <= 6 * scale)
	while (r >= 0)
	{
		temp.x = cur.x;
		temp.y = cur.y;
		cur.x = x + r * cos(rad);
		cur.y = y + r * sin(rad);
		if ((int)cur.x % scale == 0 || (int)cur.y % scale == 0 || (int)cur.x % scale == scale - 1 || (int)cur.y % scale == scale - 1)
		{
			side = set_side(cur.x, cur.y, rad);
			if (((int)cur.x % scale == 0 || (int)cur.x % scale == scale - 1) && ((int)cur.y % scale == 0 || (int)cur.y % scale == scale - 1))
				side = -1;
			// if ((int)cur.x % scale == 0 && (int)cur.y % scale == 0)
			// 	side = -1;
			if (map[(int)(cur.y / scale)][(int)(temp.x / scale)].type == WALL \
	&& map[(int)(temp.y / scale)][(int)(cur.x / scale)].type == WALL)
				return ((t_dist){temp, (t_vec2){(int)(temp.x / scale), (int)(cur.y / scale)}, side});
			if (map[(int)(cur.y / scale)][(int)(cur.x / scale)].type == WALL)
			// if (map[(int)((cur.y + sin(rad)) / scale)][(int)((cur.x + cos(rad)) / scale)].type == WALL)
				return ((t_dist){cur, (t_vec2){(int)(cur.x / scale), (int)(cur.y / scale)}, side});
		}
		r += 0.1;
	}
	return ((t_dist){cur, (t_vec2){0, 0}, -1});
}
