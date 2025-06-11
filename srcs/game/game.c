/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:23:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/11 18:33:34 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "drawline.h"
#include "map.h"

// void	put_game(t_game *game)
// {
// 	t_vec2	hit;
// 	// int		dir;
// 	float	x;
// 	float	y;
// 	t_player	mini;
//
// 	// dir = findhit(&hit, game->player, game->player.dir);
// 	hit = find_hit(game->player.dir, game->player.x, game->player.y);
// 	x = game->player.x;
// 	y = game->player.y;
// 	mini = game->minimap;
// 	drawline(game->game_t, (t_point){0xFF0000, x + mini.x, y + mini.y, 0}, (t_point){0xFF0000, hit.x + mini.x, hit.y + mini.y, 0});
// 	// pnf("%d\n", dir);
// 	// else if (dir == 2)
// 		// drawline(game->game_t, (t_point){0x0000FF, x + mini.x, y + mini.y, 0}, (t_point){0x0000FF, hit.x + mini.x, hit.y + mini.y, 0});
// }

// void	put_game(t_game *game)
// {
// 	float	i;
// 	float	h;
// 	float	s;
// 	t_player player;
// 	t_point	start;
// 	t_point	stop;
//
// 	i = -WIDTH;
// 	player = game->player;
// 	while (i < WIDTH)
// 	{
// 		h = (32 / distance(player, find_hit(player.dir, player.x, player.y), i)) *415;
// 		s = ((float)HEIGHT / 2) - (h / 2);
// 		start.color = 0xFFFFFF;
// 		start.px = ((float)WIDTH / 2) + (i / 2);
// 		start.py = s;
// 		start.outcode = 0;
// 		stop.color = 0xFFFFFF;
// 		stop.px = ((float)WIDTH / 2) + (i / 2);
// 		stop.py = h;
// 		stop.outcode = 0;
// 		drawline(game->game_t, start, stop);
// 		i++;
// 	}
// }

void	put_games(t_game *game)
{
	float		dis_left;
	float		dis_right;
	t_player	player;
	t_vec2		hit;

	player = game->player;
	hit = find_hit(player.dir - 90, player.x, player.y);
	dis_left = distance(game->player.x, game->player.y, hit);
	printf("hitL: x: %f, y: %f\n", hit.x, hit.y);
	hit = find_hit(player.dir + 90, player.x, player.y);
	dis_right = distance(game->player.x, game->player.y, hit);
	printf("hitR: x: %f, y: %f\n", hit.x, hit.y);
	printf("player: x: %f, y: %f\n", player.x, player.y);
	printf("distance: L:%.6f, R:%.6f\n", dis_left, dis_right);
}

float	cam_pos(float range, int dir, t_player player)
{
	float		dis;
	t_vec2		hit;

	hit.x = player.x;
	hit.y = player.y;
	if (dir == 1) //left
		hit = find_hit(player.dir - 90, player.x, player.y);
	else if (dir == 2) //rihght
		hit = find_hit(player.dir + 90, player.x, player.y);
	dis = distance(player.x, player.y, hit);
	if (dir == 1)
	{
		if (range > dis)
			return (dis);
		return (range);
	}
	else if (dir == 2)
	{
		if (range > dis)
			return (-dis);
		return (-range);
	}
	return (dis);
}

void	put_game(t_game *game)
{
	float	fov = WIDTH;
	int		i;
	float	campos;
	t_player player;
	float	h;
	float	s;
	t_point	start;
	t_point	stop;

	i = -(fov / 2);
	player = game->player;
	while (i < fov / 2)
	{
		if (i < 0)
			campos = cam_pos(i / (float)100, 1, player);
		else
		{
			campos = cam_pos(i / (float)100, 2, player);
		}
		// campos = 0;
		h = (32 / distance(player.x + campos * cos(player.dir * PI / 180), player.y, find_hit(player.dir, player.x + campos * cos(player.dir * PI / 180), player.y))) * 415;
		ft_texture(game->game_t, player.x + campos * cos(player.dir * PI / 180) + game->minimap.x, player.y + game->minimap.y, 0x000000);
		s = ((float)HEIGHT / 2) - (h / 2);
		start.color = 0xFFFFFF;
		start.px = ((float)WIDTH / 2) + (i / (float)2);
		start.py = s;
		start.outcode = 0;
		stop.color = 0xFFFFFF;
		stop.px = ((float)WIDTH / 2) + (i / (float)2);
		stop.py = h;
		stop.outcode = 0;
		drawline(game->game_t, start, stop);
		i++;
	}
}
