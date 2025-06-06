/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:56:42 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 18:05:53 by knakto           ###   ########.fr       */
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
	float		padding;
	t_point		front;
	t_point		left;
	t_point		right;
	float		redian;

	padding = 15;
	redian = player.dir * PI / 180;
	front.color = color;
	front.outcode = 0;
	front.px = player.x + padding * cos(redian);
	front.py = player.y + padding * sin(redian);
	left.color = color;
	left.outcode = 0;
	left.px = player.x + (padding / 3) * cos(redian - PI / 1.5);
	left.py = player.y + (padding / 3) * sin(redian - PI / 1.5);
	right.color = color;
	right.outcode = 0;
	right.px = player.x + (padding / 3) * cos(redian + PI / 1.5);
	right.py = player.y + (padding / 3) * sin(redian + PI / 1.5);
	bresenham(text, front, left);
	bresenham(text, front, right);
	bresenham(text, left, right);
	ft_texture(text, player.x, player.y, color);
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
