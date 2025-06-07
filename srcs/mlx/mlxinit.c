/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:48:12 by knakto            #+#    #+#             */
/*   Updated: 2025/06/07 17:25:07 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include "map.h"
#include "ray.h"

void	con(void *mlx)
{
	// mlx_image_t		*img;
	mlx_texture_t	*minimap;
	t_game			*game;

	// (void)mlx;
	game = get_game();
	bind(mlx);
	if (game->on_change)
		return ;
	minimap = new_texture(WIDTH, HEIGHT, 0x000000);
	print_map(mlx, minimap);
	// img = mlx_texture_to_image(mlx, text);
	// mlx_image_to_window(mlx, img, 0, 0);
	// mlx_delete_image(mlx, img);
	mlx_delete_texture(minimap);
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
