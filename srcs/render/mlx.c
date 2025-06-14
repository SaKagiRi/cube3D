/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:02:17 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 14:16:43 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "game.h"
#include "render.h"

static void	inti(t_game *game)
{
	game->minimap.x = (int)(MINI_WIDTH / 2) - game->player.x;
	game->minimap.y = (int)(MINI_HEIGHT / 2) - game->player.y;
	game->player.dir_y = 0;
	game->player.z = 0;
	game->player.dir_x -= 90;
	if (game->player.dir_x < 0)
		game->player.dir_x = 360 + game->player.dir_x;
	game->mlx = mlx_init(WIDTH, HEIGHT, "game", true);
	game->game_t = new_texture(WIDTH, HEIGHT, 0x000000);
	game->on_change = false;
}

void	mlx(void)
{
	t_game	*game;

	game = get_game();
	inti(game);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(game->mlx, hook, game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
