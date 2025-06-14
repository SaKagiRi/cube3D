/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:07:49 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 13:58:11 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include "render.h"
#include <math.h>

bool	bindgame(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	else
		return (0);
	game->on_change = false;
	return (1);
}

void	keybind(t_game	*game)
{
	bindwalk(game);
	bindgame(game);
	bindswing(game);
}

void	key_hook(mlx_key_data_t data, void	*in)
{
	t_game	*game;
	float	bonus_speed;

	game = (t_game *)in;
	bonus_speed = 0.2;
	if (data.key == MLX_KEY_LEFT_SHIFT && data.action == 1)
		game->player_speed += bonus_speed;
	else if (data.key == MLX_KEY_LEFT_SHIFT && data.action == 0)
		game->player_speed -= bonus_speed;
	else if (data.key == MLX_KEY_LEFT_CONTROL && data.action == 1)
		game->player_speed -= bonus_speed;
	else if (data.key == MLX_KEY_LEFT_CONTROL && data.action == 0)
		game->player_speed += bonus_speed;
	else if (data.key == MLX_KEY_SPACE && data.action == 1 && !game->on_jump)
		game->on_jump = true;
	else if (data.key == MLX_KEY_G && data.action == 1)
	{
		game->player.dir_x -= 180;
		allow_dir(game);
	}
	else
		return ;
	game->on_change = false;
}
