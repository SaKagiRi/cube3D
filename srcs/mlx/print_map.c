/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:56:42 by knakto            #+#    #+#             */
/*   Updated: 2025/06/08 17:48:02 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include "map.h"
#include "ray.h"
#include "drawline.h"
#include <math.h>

void	put_box(mlx_texture_t *text, int x, int y, size_t color)
{
	int		scale;
	int		i;
	int		j;

	scale = get_game()->scale;
	x -= scale;
	y -= scale;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			if (x + i < MINI_WIDTH && y + j < MINI_HEIGHT)
				ft_texture(text, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	print_map(mlx_t *mlx, mlx_texture_t *text)
{
	t_game		*game;
	t_map			map;
	mlx_image_t		*img;
	unsigned int	i;
	unsigned int	j;

	(void)mlx;
	game = get_game();
	if (game->first_render)
		game->first_render = false;
	else
	{
		mlx_delete_image(game->mlx, game->minimap_i);
		// mlx_delete_image(game->mlx, game->game_i);
	}
	put_game(game->minimap_t);
	map = game->map;
	i = 0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j].type != END)
		{
			if (map.map[i][j].type == PATH)
				put_box(text, map.map[i][j].x + game->minimap.x, map.map[i][j].y + game->minimap.y, 0xFFFFFF);
			else if (map.map[i][j].type == WALL)
				put_box(text, map.map[i][j].x + game->minimap.x, map.map[i][j].y + game->minimap.y, 0xAAAAAA);
			j++;
		}
		i++;
	}
	put_player(text, game->player, 0xFF0000);
	// printf("player: %f, %f\n", get_game()->player.x, get_game()->player.y);
	putray(text);
	// pnf("pass\n");
	img = mlx_texture_to_image(game->mlx, text);
	mlx_image_to_window(game->mlx, img, 10, 10);
	game->minimap_i = img;
}
