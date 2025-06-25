/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:22:00 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:33:50 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube.h"
# include "../ray/ray.h"

void			put_map(t_game *game);
void			put_player(mlx_texture_t *text, t_player player, size_t color);
void			put_game(t_game *game);

void			set_ray_fov(t_game *game, t_ray ray[100]);
void			put_fov(t_game *game);

t_vec2			wallcheck(float x, float y, float dir, float speed);

int				set_side_wall(t_dist hit);
mlx_texture_t	*get_side(t_game *game, int side);
void			set_background(t_game *game);
size_t			apply_fog(size_t color, float distance, float max_distance);

void			dda(t_game *game);
void			set_background(t_game *game);
t_vec2			get_gap(t_game *game, t_vec2 hit);

void			teleport(t_game *game);
void			set_teleport(t_game *game, t_player player, int sw);
bool			tp_check(t_game *game, t_player player, int sw);
void			reset_teleport(t_game *game, int sw);
t_vec2			get_tp_point(t_game *game, int sw);

#endif
