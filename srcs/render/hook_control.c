/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:04:18 by knakto            #+#    #+#             */
/*   Updated: 2025/06/13 05:05:41 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	check_render(t_game *game)
{
	keybind(game);
	if (game->on_change)
		return (true);
	mlx_delete_image(game->mlx, game->game_i);
	return (false);
}

static void	render(t_game *game)
{
	game->game_i = mlx_texture_to_image(game->mlx, game->game_t);
	mlx_image_to_window(game->mlx, game->game_i, 0, 0);
	fill_background(game->game_t, 0x000000);
	game->on_change = true;
}

void	hook(void *data)
{
	t_game		*game;

	game = (t_game *)data;
	if (check_render(game))
		return ;
	put_map(game);
	put_player(game->game_t, game->player, 0x000000FF);
	render(game);
}
