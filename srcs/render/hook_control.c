/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 02:04:18 by knakto            #+#    #+#             */
/*   Updated: 2025/06/22 17:55:10 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "game.h"
#include "render.h"

static bool	check_render(t_game *game)
{
	keybind(game);
	jump(game);
	mouse(game);
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

void	put_cursor(t_game *game)
{
	int		i;

	i = 0;
	while (i <= 10)
		ft_texture(game->game_t, WIDTH / 2.0f - 5 + i++, HEIGHT / 2.0f, 0xFFFFFF);
	i = 0;
	while (i <= 10)
		ft_texture(game->game_t, WIDTH / 2.0f, HEIGHT / 2.0f - 5 + i++, 0xFFFFFF);
}

void	hook(void *data)
{
	t_game		*game;

	game = (t_game *)data;
	if (check_render(game))
		return ;
	set_background(game);
	put_game(game);
	put_map(game);
	put_player(game->game_t, game->player, 0x000000FF);
	put_cursor(game);
	render(game);
}
