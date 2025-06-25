/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:20:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/25 23:37:40 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "../../include/cube.h"
#include "drawline.h"
#include "cube.h"
#include "game.h"
#include <math.h>
#include <stdlib.h>

static bool	scale_step(double *r, double *step, int *count)
{
	if (*count == 4)
		return (true);
	*r -= *step;
	*step /= 10;
	*count += 1;
	return (false);
}

static bool	wall_check(t_vec2 cur, t_vec2 temp, int mode)
{
	t_tile	**map;

	map = get_game()->map.map;
	if (mode == 0)
		return ((int)cur.x % SCALE == 0 || (int)cur.y % SCALE == 0 \
|| (int)cur.x % SCALE == SCALE - 1 || (int)cur.y % SCALE == SCALE - 1);
	else if (mode == 1)
		return (map[(int)(cur.y / SCALE)][(int)(temp.x / SCALE)].type == WALL \
&& map[(int)(temp.y / SCALE)][(int)(cur.x / SCALE)].type == WALL);
	else if (mode == 2)
		return (map[(int)(cur.y / SCALE)][(int)(cur.x / SCALE)].type == WALL);
	return (false);
}

static void	init_ray(double *r, double *s, int *c)
{
	*r = 0;
	*s = 1;
	*c = 0;
}

static int	sub_fnc_find_hit(t_vec2 cur, t_vec2 temp, t_vec2 *range, int *count)
{
	if (wall_check(cur, temp, 0))
	{
		if (wall_check(cur, temp, 1))
		{
			if (scale_step(&range->x, &range->y, count))
				return (1);
		}
		else if (wall_check(cur, temp, 2))
			if (scale_step(&range->x, &range->y, count))
				return (2);
	}
	return (0);
}

t_dist	find_hit(float ray_angle, float x, float y)
{
	t_vec2	cur;
	t_vec2	temp;
	t_vec2	range;
	int		status;
	int		c;

	init_ray(&range.x, &range.y, &c);
	cur.x = x;
	cur.y = y;
	while (range.x >= 0)
	{
		temp.x = cur.x;
		temp.y = cur.y;
		cur.x = x + range.x * cos(ray_angle * PI / 180);
		cur.y = y + range.x * sin(ray_angle * PI / 180);
		status = sub_fnc_find_hit(cur, temp, &range, &c);
		if (status == 1)
			return (cast_t_dist(temp, cur, 0));
		else if (status == 2)
			return (cast_t_dist(temp, cur, 1));
		range.x += range.y;
	}
	return ((t_dist){cur, (t_vec2){0, 0}, -1, 0});
}
