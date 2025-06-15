/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:22:00 by knakto            #+#    #+#             */
/*   Updated: 2025/06/16 00:52:06 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube.h"
# include "../ray/ray.h"

void	put_map(t_game *game);
void	put_player(mlx_texture_t *text, t_player player, size_t color);
void	put_game(t_game *game);

void	set_ray_fov(t_game *game, t_ray ray[100]);
void	put_fov(t_game *game);

t_vec2	wallcheck(float x, float y, float dir, float speed);

void	dda(t_game *game);

#endif
