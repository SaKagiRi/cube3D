/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:27 by knakto            #+#    #+#             */
/*   Updated: 2025/06/11 18:16:49 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "cube.h"

// int	findhit(t_vec2 *hit, t_player player, float ray_angle);
t_vec2	find_hit(float ray_angle, float x, float y);
float	distance(float px, float py, t_vec2 hit);

#endif
