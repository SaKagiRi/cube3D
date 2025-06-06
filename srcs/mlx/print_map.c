/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:56:42 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 17:20:42 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"
#include "game.h"
#include "map.h"
#include "drawline.h"
#include <math.h>

void	put_player(mlx_texture_t *text, t_player player, size_t color)
{
	int		padding;
	float		i;
	float		j;
	float		redian;

	padding = 2;
	i = -padding;
	while (i < padding)
	{
		j = -padding;
		while (j < padding)
		{
			ft_texture(text, player.x + i, player.y + j, color);
			j++;
		}
		i++;
	}
	redian = player.dir * PI / 180;
	i = player.x + 50 * cos(redian);
	j = player.y + 50 * sin(redian);
	printf("%f\n", player.dir);
	// pnf("%d, %d -> %d, %d", player.x, player.y, i, j);
	bresenham(text, (t_point){0xFF0000, player.x, player.y, 0}, (t_point){0xFF0000, i, j, 0});

}

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
			ft_texture(text, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	print_map(mlx_t *mlx, mlx_texture_t *text)
{
	t_map			map;
	mlx_image_t		*img;
	unsigned int	i;
	unsigned int	j;

	(void)mlx;
	if (get_game()->first_render)
		get_game()->first_render = false;
	else
		mlx_delete_image(get_game()->mlx, get_game()->img);
	map = get_game()->map;
	i = 0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j].type != END)
		{
			if (map.map[i][j].type == PATH)
				put_box(text, map.map[i][j].x, map.map[i][j].y, 0xFFFFFF);
			else if (map.map[i][j].type == WALL)
				put_box(text, map.map[i][j].x, map.map[i][j].y, 0x00FF00);
			j++;
		}
		i++;
	}
	put_player(text, get_game()->player, 0xFF0000);
	img = mlx_texture_to_image(get_game()->mlx, text);
	mlx_image_to_window(get_game()->mlx, img, 0, 0);
	get_game()->img = img;
}
