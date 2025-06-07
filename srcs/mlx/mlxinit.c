/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:48:12 by knakto            #+#    #+#             */
/*   Updated: 2025/06/07 12:28:39 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include "map.h"

void	con(void *mlx)
{
	// mlx_image_t		*img;
	mlx_texture_t	*text;
	t_game			*game;

	// (void)mlx;
	game = get_game();
	bind(mlx);
	if (game->on_change)
		return ;
	text = new_texture(WIDTH, HEIGHT, 0x000000);
	print_map(mlx, text);
	// img = mlx_texture_to_image(mlx, text);
	// mlx_image_to_window(mlx, img, 0, 0);
	// mlx_delete_image(mlx, img);
	mlx_delete_texture(text);
	game->on_change = true;
}

void	mlx(void)
{
	t_game	*game;

	game = get_game();
	game->on_change = false;
	game->mlx = mlx_init(WIDTH, HEIGHT, "game", true);
	// mlx_key_hook(game->mlx, bind, game->mlx);
	mlx_loop_hook(game->mlx, con, game->mlx);
	pnf("hello\n");
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
