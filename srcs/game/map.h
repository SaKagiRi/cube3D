/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:22:00 by knakto            #+#    #+#             */
/*   Updated: 2025/06/13 05:02:20 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cube.h"
# include "../ray/ray.h"

void	put_map(t_game *game);
void	put_player(mlx_texture_t *text, t_player player, size_t color);
void	put_game(t_game *game);

t_vec2	wallcheck(float x, float y, float dir, float speed);

#endif
