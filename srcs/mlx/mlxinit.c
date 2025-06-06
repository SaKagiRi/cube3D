/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:48:12 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 18:05:15 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include "map.h"
#include <math.h>

void	con(void *mlx)
{
	// mlx_image_t		*img;
	mlx_texture_t	*text;

	// (void)mlx;
	bind(mlx);
	if (get_game()->on_change)
		return ;
	text = new_texture(WIDTH, HEIGHT, 0x000000);
	print_map(mlx, text);
	// img = mlx_texture_to_image(mlx, text);
	// mlx_image_to_window(mlx, img, 0, 0);
	// mlx_delete_image(mlx, img);
	mlx_delete_texture(text);
	get_game()->on_change = true;
}

void	mlx(void)
{
	get_game()->on_change = false;
	get_game()->mlx = mlx_init(WIDTH, HEIGHT, "game", true);
	// mlx_key_hook(get_game()->mlx, bind, get_game()->mlx);
	mlx_loop_hook(get_game()->mlx, con, get_game()->mlx);
	pnf("hello\n");
	mlx_loop(get_game()->mlx);
	mlx_terminate(get_game()->mlx);
}
