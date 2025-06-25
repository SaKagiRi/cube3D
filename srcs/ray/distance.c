/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 00:02:45 by knakto            #+#    #+#             */
/*   Updated: 2025/06/25 23:17:20 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

float	distance(float px, float py, t_vec2 hit, float dir)
{
	float	dx;
	float	dy;
	float	dis;
	float	rad;

	dx = hit.x - px;
	dy = hit.y - py;
	dis = sqrt(dx * dx + dy * dy);
	rad = dir * PI / 180;
	return (dis * cos(rad));
}

t_dist	cast_t_dist(t_vec2 temp, t_vec2 cur, int mode)
{
	if (mode == 0)
		return ((t_dist){temp, (t_vec2){(int)(temp.x / SCALE),
			(int)(cur.y / SCALE)}, -1, 0});
	else
		return ((t_dist){cur, (t_vec2){(int)(cur.x / SCALE),
			(int)(cur.y / SCALE)}, -1, 0});
}
