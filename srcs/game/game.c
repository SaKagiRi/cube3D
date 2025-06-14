/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:23:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/14 14:06:19 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "cube.h"
#include "drawline.h"
#include "map.h"
#include "unistd.h"

// void	put_games(t_game *game) { float		dis_left; float		dis_right; t_player	player; t_vec2		hit; player = game->player; hit = find_hit(player.dir - 90, player.x, player.y); dis_left = distance(game->player.x, game->player.y, hit); printf("hitL: x: %f, y: %f\n", hit.x, hit.y); hit = find_hit(player.dir + 90, player.x, player.y); dis_right = distance(game->player.x, game->player.y, hit); printf("hitR: x: %f, y: %f\n", hit.x, hit.y); printf("player: x: %f, y: %f\n", player.x, player.y); printf("distance: L:%.6f, R:%.6f\n", dis_left, dis_right); } float	cam_pos(float range, int dir, t_player player) { float		dis; t_vec2		hit; hit.x = player.x; hit.y = player.y;
// 	if (dir == 1) //left
// 		hit = find_hit(player.dir - 90, player.x, player.y);
// 	else if (dir == 2) //rihght
// 		hit = find_hit(player.dir + 90, player.x, player.y);
// 	dis = distance(player.x, player.y, hit);
// 	if (dir == 1)
// 	{
// 		if (range > dis)
// 			return (dis);
// 		return (range);
// 	}
// 	else if (dir == 2)
// 	{
// 		if (range > dis)
// 			return (-dis);
// 		return (-range);
// 	}
// 	return (dis);
// }

size_t	set_wall_color(t_dist hit)
{
	if (hit.side == NORTH)
		return (0xFFFFFF);
	else if (hit.side == WEST)
		return (0xFF0000);
	else if (hit.side == SOUTH)
		return (0x00FF00);
	else if (hit.side == EAST)
		return (0x0000FF);
	return (0x000000);
}

float get_rad(float ax, float ay, float bx, float by)
{
	return atan2(by - ay, bx - ax);
}

void	print_wall(t_point	p[4])
{
	float	rad_top;
	float	rad_down;
	float	dist;
	float	i;

	rad_top = get_rad(p[0].px, p[0].py, p[2].px, p[2].py);
	rad_down = get_rad(p[1].px, p[1].py, p[3].px, p[3].py);
	dist = sqrt((p[2].px - p[0].px) * (p[2].px - p[0].px) + (p[2].py - p[0].py) * (p[2].py - p[0].py));
	i = 0;
	drawline(get_game()->game_t, p[0], p[1]);
	while (i < dist)
	{
		p[0].px += cos(rad_top);
		p[0].py += sin(rad_top);
		p[1].px += cos(rad_down);
		p[1].py += sin(rad_down);
		drawline(get_game()->game_t, p[0], p[1]);
		i += 0.1;
	}
}

t_dist	fhit(t_player player, int i, int scale, t_game *game)
{
	float	j;
	t_dist	hit;

	j = 0;
	while (j < 1)
	{
		hit = find_hit(player.dir_x + i + j, player.x, player.y);
		if (hit.ishit && ((int)hit.hit.x % scale == 0 || (int)hit.hit.x % scale == scale - 1) \
&& ((int)hit.hit.y % scale == 0 || (int)hit.hit.y % scale == scale - 1))
		{
			drawline(game->game_t, (t_point){0x0000FF, player.x + game->minimap.x, player.y + game->minimap.y, 0}, (t_point){0x0000FF, hit.hit.x + game->minimap.x, hit.hit.y + game->minimap.y, 0});
			return (hit);
		}
		j += 0.2;
	}
	hit.ishit = false;
	return (hit);
}

void	set_ray_fov(t_game *game, t_ray ray[100])
{
	float	fov;
	float	block;
	int		i;

	fov = 30;
	i = 0;
	block = fov / WIDTH;
	(void)game;
	while (i < 100)
	{
		ray[i].start_x = i * block;
		ray[i].point.px = i * block;
		ray[i].hit = fhit(game->player, i, game->scale, game);
		ray[i].point.py = 0;
		ray[i].point.color = 0xFFFFFF;
		ray[i].point.outcode = 0;
		i++;
	}
}

void	put_fov(t_game *game)
{
	t_ray	ray[100];
	int		i;

	set_ray_fov(game, ray);
	i = 0;
	while (i < 100)
	{
		drawline(game->game_t, ray[i].point, (t_point){0xFFFFFF, ray[i].start_x, HEIGHT, 0});
		i++;
	}
}

void	put_game(t_game *game)
{
	float	fov = 60;
	float		i;
	t_player player;
	float	h;
	float	s;
	t_point	start;
	t_point	stop;
	float	dist;
	t_dist	hit;
	float	step;
	// float	rad;

	i = -(fov / 2);
	player = game->player;
	step = fov / WIDTH;
	// printf("%f\n", step);
	while (i < fov / 2)
	{	
		// hit = fhit(player, i, game->scale, game);
		printf("%f\n", i);
		hit = find_hit(player.dir_x + i, player.x, player.y);
		dist = distance(player.x, player.y, hit.hit, i);
		h = (40 / dist) * (WIDTH / 2.0f);
		ft_texture(game->game_t, player.x + game->minimap.x, player.y + game->minimap.y, 0x000000);
		drawline(game->game_t, (t_point){0x0000FF, player.x + game->minimap.x, player.y + game->minimap.y, 0}, (t_point){0x0000FF, hit.hit.x + game->minimap.x, hit.hit.y + game->minimap.y, 0});
		s = (HEIGHT - h) / 2;
		start.color = set_wall_color(hit);
		start.outcode = 0;
		stop.color = set_wall_color(hit);
		stop.outcode = 0;
		start.py = s + (player.z * 30/ dist) + player.dir_y;
		stop.py = h + s + (player.z * 30 / dist) + player.dir_y;
		if (!hit.ishit)
		{
			i += step;
			continue ;
		}
		start.px = ((float)WIDTH / 2) + i * fov;
		stop.px = ((float)WIDTH / 2) + i * fov;
		drawline(game->game_t, start, stop);
		i += step;
	}
}
