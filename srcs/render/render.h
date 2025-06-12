/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:05:00 by knakto            #+#    #+#             */
/*   Updated: 2025/06/13 06:15:03 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cube.h"
# include "../game/map.h"

void	hook(void *game);
void	keybind(t_game	*game);
void	key_hook(mlx_key_data_t data, void	*in);
bool	bindwalk(t_game *game);
bool	bindswing(t_game *game);
void	allow_dir(t_game *game);

#endif
