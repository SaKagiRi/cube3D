/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:07:49 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:00:20 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "unistd.h"

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

static bool	hook_move(mlx_key_data_t data, t_game *game)
{
	float	bonus_speed;

	bonus_speed = 0.2;
	if (data.key == MLX_KEY_LEFT_SHIFT && data.action == 1)
		game->player_speed += bonus_speed;
	else if (data.key == MLX_KEY_LEFT_SHIFT && data.action == 0)
		game->player_speed -= bonus_speed;
	else if (data.key == MLX_KEY_LEFT_CONTROL && data.action == 1)
	{
		game->player_speed -= bonus_speed;
		game->player.dir_y -= 50;
	}
	else if (data.key == MLX_KEY_LEFT_CONTROL && data.action == 0)
	{
		game->player_speed += bonus_speed;
		game->player.dir_y = 0;
	}
	else if (data.key == MLX_KEY_SPACE && data.action == 1 && !game->on_jump)
		game->on_jump = true;
	else
		return (false);
	return (true);
}

static bool	hook_ability(mlx_key_data_t data, t_game *game)
{
	if (data.key == MLX_KEY_G && data.action == 1)
	{
		game->player.dir_x -= 180;
		allow_dir(game);
	}
	else if (data.key == MLX_KEY_F && data.action == 1)
		game->fog = !game->fog;
	else if (data.key == MLX_KEY_Q && data.action == 1)
		set_teleport(game, game->player, 1);
	else if (data.key == MLX_KEY_E && data.action == 1)
		set_teleport(game, game->player, 2);
	else if (data.key == MLX_KEY_R && data.action == 1)
	{
		reset_teleport(game, 1);
		reset_teleport(game, 2);
	}
	else
		return (false);
	return (true);
}

void	key_hook(mlx_key_data_t data, void	*in)
{
	t_game	*game;

	game = (t_game *)in;
	if (hook_move(data, game) || hook_ability(data, game))
		game->on_change = false;
}
