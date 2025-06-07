/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:18:45 by knakto            #+#    #+#             */
/*   Updated: 2025/06/07 16:49:17 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "cube.h"
#include "drawline.h"
#include "game.h"
#include <math.h>

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

double	distance(float px, float py, float hx, float hy);
t_vec2	find_hit(float rad, float x, float y);
void	putray(mlx_texture_t *text);

#endif
