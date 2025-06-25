/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:27 by knakto            #+#    #+#             */
/*   Updated: 2025/06/25 23:17:33 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "cube.h"

typedef enum e_dir
{
	NORTH,
	EAST,
	WEST,
	SOUTH
}	t_dir;

typedef struct s_dist
{
	t_vec2	hit;
	t_vec2	block;
	int		side;
	float	dist;
}	t_dist;

typedef struct s_ray
{
	bool	is_show;
	t_dist	hit;
	float	start_x;
	t_point	point;
}	t_ray;

t_dist	find_hit(float ray_angle, float x, float y);
float	distance(float px, float py, t_vec2 hit, float dir);
t_dist	cast_t_dist(t_vec2 temp, t_vec2 cur, int mode);

#endif
