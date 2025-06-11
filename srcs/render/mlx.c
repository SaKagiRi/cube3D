/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:02:17 by knakto            #+#    #+#             */
/*   Updated: 2025/06/10 19:24:02 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	inti(t_game *game)
{
	game->minimap.x = (int)(MINI_WIDTH / 2) - game->player.x;
	game->minimap.y = (int)(MINI_HEIGHT / 2) - game->player.y;
	game->player.outcode = 0;
	game->player.dir -= 90;
	if (game->player.dir < 0)
		game->player.dir = 360 + game->player.dir;
	game->mlx = mlx_init(WIDTH, HEIGHT, "game", true);
	game->game_t = new_texture(WIDTH, HEIGHT, 0x000000);
	game->on_change = false;
}

void	mlx(void)
{
	t_game	*game;

	game = get_game();
	inti(game);
	mlx_loop_hook(game->mlx, hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
