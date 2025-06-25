/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:23:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/23 23:39:19 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "MLX42.h"
#include "cube.h"
#include "drawline.h"
#include "endian.h"
#include "map.h"
#include "stdlib.h"
#include "unistd.h"

t_vec2	get_gap(t_game *game, t_vec2 hit)
{
	t_vec2		gap;

	gap.x = 0;
	gap.y = 0;
	while (hit.y - gap.y > 0 && hit.y - gap.y < game->map.row * SCALE)
	{
		if ((int)(hit.y - gap.y) % 10 == 0)
			break ;
		gap.y += 0.01;
	}
	while (hit.x - gap.x > 0 && hit.x - gap.x < game->map.col * SCALE)
	{
		if ((int)(hit.x - gap.x) % 10 == 0)
			break ;
		gap.x += 0.01;
	}
	return (gap);
}

size_t	sub_fnc_texture_wall(size_t rgba, t_vec2 gap, t_dist hit, t_game *game)
{
	if (gap.x >= 1.5 && gap.x <= 7 \
&& game->teleport.tp_left.x == hit.block.x \
&& game->teleport.tp_left.y == hit.block.y \
&& game->teleport.side_left == hit.side)
		rgba = 0x0000FFFF;
	if (gap.x >= 1.5 && gap.x <= 7 \
&& game->teleport.tp_right.x == hit.block.x \
&& game->teleport.tp_right.y == hit.block.y \
&& game->teleport.side_right == hit.side)
		rgba = 0xFF0000FF;
	if (game->fog && hit.dist > 10)
		rgba = apply_fog(rgba, hit.dist, 9 * SCALE);
	return (rgba);
}

void	fill_texture_wall(t_game *game, t_vec2 start, float height, t_dist hit)
{
	t_vec2			gap;
	t_vec2			step;
	mlx_texture_t	*text;
	int				i;
	size_t			rgba;

	gap = get_gap(game, hit.hit);
	if (hit.side == EAST || hit.side == WEST)
		gap.x = gap.y;
	step.x = gap.x / SCALE;
	text = get_side(game, hit.side);
	if (!text)
		return ;
	if (step.x == 0)
		step.x = 0.1;
	step.y = (int)text->height / height;
	i = 0;
	while (i < height)
	{
		ft_texture_color(text, step.x * text->width, i * step.y, &rgba);
		rgba = sub_fnc_texture_wall(rgba, gap, hit, game);
		if (start.y + i > 0 && start.y + i < HEIGHT)
			ft_texture(game->game_t, start.x, start.y + i, rgba);
		i++;
	}
}

void	set_wall(t_game *game, t_player player, float ray_angle)
{
	t_dist		hit;
	float		height;
	float		start;
	float		stop;
	float		x;

	hit = find_hit(player.dir_x + (ray_angle), player.x, player.y);
	hit.dist = distance(player.x, player.y, hit.hit, (ray_angle));
	if (hit.dist < 2)
		hit.dist = 2;
	hit.side = set_side_wall(hit);
	height = (28 / hit.dist) * (WIDTH / 3.7f);
	start = ((HEIGHT - height) / 2);
	stop = height + start + (player.z * 30 / hit.dist) + player.dir_y;
	start += (player.z * 30 / hit.dist) + player.dir_y;
	x = ((float)WIDTH / 2) + ray_angle * (WIDTH / game->fov);
	fill_texture_wall(game, (t_vec2){x, start}, stop - start, hit);
}

void	put_game(t_game *game)
{
	float		ray_angle;
	t_player	player;
	float		step;
	int			i;

	ray_angle = -(game->fov / 2);
	player = game->player;
	step = game->fov / WIDTH;
	i = 0;
	while (ray_angle < game->fov / 2)
	{
		if (i % 1 == 0)
			set_wall(game, player, ray_angle);
		i++;
		ray_angle += step;
	}
}
