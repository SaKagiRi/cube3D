/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:20:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/22 20:22:36 by knakto           ###   ########.fr       */
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

bool	scale_step(float *r, float *step, int *count)
{
	if (*count == 4)
		return (true);
	*r -= *step;
	*step /= 10;
	*count += 1;
	return (false);
}

t_dist	find_hit(float ray_angle, float x, float y)
{
	t_vec2	cur;
	t_vec2	temp;
	float	r;
	float	s;
	int		c;
	t_tile	**map;
	int		scale;
	float	rad;

	r = 0;
	map = get_game()->map.map;
	scale = SCALE;
	rad = ray_angle * PI / 180;
	cur.x = x;
	cur.y = y;
	s = 1;
	c = 0;
	while (r >= 0)
	{
		temp.x = cur.x;
		temp.y = cur.y;
		cur.x = x + r * cos(rad);
		cur.y = y + r * sin(rad);
		if ((int)cur.x % scale == 0 || (int)cur.y % scale == 0 || (int)cur.x % scale == scale - 1 || (int)cur.y % scale == scale - 1)
		{
			if (map[(int)(cur.y / scale)][(int)(temp.x / scale)].type == WALL \
	&& map[(int)(temp.y / scale)][(int)(cur.x / scale)].type == WALL)
			{
				if (scale_step(&r, &s, &c))
					return ((t_dist){temp, (t_vec2){(int)(temp.x / scale), (int)(cur.y / scale)}, -1, 0});
			}
			else if (map[(int)(cur.y / scale)][(int)(cur.x / scale)].type == WALL)
				if (scale_step(&r, &s, &c))
					return ((t_dist){cur, (t_vec2){(int)(cur.x / scale), (int)(cur.y / scale)}, -1, 0});
		}
		r += s;
	}
	return ((t_dist){cur, (t_vec2){0, 0}, -1, 0});
}
