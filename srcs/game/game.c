/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:23:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/16 03:35:25 by kawaii           ###   ########.fr       */
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

void	put_smoke(t_game *game, float i, float fov)
{
	int		j;
	float	h;
	t_point	start;
	t_point	stop;
	t_player	player;

	j = 0;
	player = game->player;
	h = (40.0f / 60.0f) * (WIDTH / 3.7f);
	start.color = 0x888888;
	start.outcode = 0;
	stop.color = 0x888888;
	stop.outcode = 0;
	start.py = ((HEIGHT - h) / 2) + (player.z * 30 / 60.0f) + player.dir_y;
	stop.py = h + ((HEIGHT - h) / 2) + (player.z * 30 / 60.0f) + player.dir_y;
	while (j < 4)
	{
		start.px = ((float)WIDTH / 2) + i * fov + j;
		stop.px = ((float)WIDTH / 2) + i * fov + j;
		drawline(game->game_t, start, stop);
		j++;
	}
}

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

size_t apply_fog(size_t color, float distance, float max_distance)
{
    float fog_intensity = distance / max_distance;
    if (fog_intensity > 1.0f) fog_intensity = 1.0f;
    if (fog_intensity < 0.0f) fog_intensity = 0.0f;

    // สีเดิม
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    // สีหมอก (0x646464)
    uint8_t fog_r = 0x30;
    uint8_t fog_g = 0x30;
    uint8_t fog_b = 0x30;

    // ผสมสี
    uint8_t new_r = r * (1.0f - fog_intensity) + fog_r * fog_intensity;
    uint8_t new_g = g * (1.0f - fog_intensity) + fog_g * fog_intensity;
    uint8_t new_b = b * (1.0f - fog_intensity) + fog_b * fog_intensity;

    return (new_r << 16) | (new_g << 8) | new_b;
}

void	put_bg_fog(t_game *game, size_t bg_top, size_t bg_down)
{
	int		i, j;
	size_t color;
	float	horizon = HEIGHT / 2.0f + game->player.dir_y;
	float	max_depth = HEIGHT / 2.0f;

	i = 0;
	while (i < HEIGHT + 600)
	{
		float depth = fabsf(i - horizon);
		float fog_intensity = depth / max_depth;
		if (fog_intensity > 1.0f)
			fog_intensity = 1.0f;

		color = i;
		if (i < horizon)
			color = apply_fog(bg_top, 80 - (fog_intensity * 80),  80);
		else
			color = apply_fog(bg_down, 80 - (fog_intensity * 80), 80);

		j = 0;
		while (j < WIDTH)
		{
			ft_texture(game->game_t, j, i, color);
			j++;
		}
		i++;
	}
}

void	put_bg(t_game *game, size_t bg_top, size_t bg_down)
{
	int		i;
	int		j;
	size_t	color;

	i = 0;
	color = bg_top;
	while (i < HEIGHT + 600)
	{
		if (i >= (HEIGHT / 2.0f) + game->player.dir_y)
			color = bg_down;
		j = 0;
		while (j < WIDTH)
		{
			ft_texture(game->game_t, j, i, color);
			j++;
		}
		i++;
	}
}

int	get_direction_from_rad(float rad)
{
	// ปรับมุมให้อยู่ในช่วง 0 - 2π
	rad = fmodf(rad, 2 * M_PI);
	if (rad < 0)
		rad += 2 * M_PI;

	if (rad >= 7 * M_PI / 4 || rad < M_PI / 4)
		return EAST;
	else if (rad >= M_PI / 4 && rad < 3 * M_PI / 4)
		return SOUTH;
	else if (rad >= 3 * M_PI / 4 && rad < 5 * M_PI / 4)
		return WEST;
	else
		return NORTH;
}

int	get_block_side(float center_x, float center_y, float hit_x, float hit_y)
{
	float dx = hit_x - center_x;
	float dy = hit_y - center_y;

	if (fabs(dx) >= fabs(dy))
	{
		if (dx > 0)
			return EAST;
		else
			return WEST;
	}
	else
	{
		if (dy > 0)
			return SOUTH;
		else
			return NORTH;
	}
}

int	set_side_wall(t_dist hit)
{
	float	center_x;
	float	center_y;

	if (hit.block.x == 0 && hit.block.y == 0)
		return (-1);
	center_x = (hit.block.x * SCALE) + (SCALE / 2.0f);
	center_y = (hit.block.y * SCALE) + (SCALE / 2.0f);
	// printf("cx:%f, cy:%f\n, hx:%f, hy:%f\n\n\n", center_x, center_y, hit.hit.x, hit.hit.y);
	return (get_block_side(center_x, center_y, hit.hit.x, hit.hit.y));
}

// int		set_side_wall(float px, float py, float hx, float hy)
// {
// 	float	dx;
// 	float	dy;
//
// 	dx = hx - px;
// 	dy = hy - py;
// 	if (fabs(dx) > fabs(dy))
// 	{
// 		if (dx > 0)
// 			return (WEST);
// 		else
// 			return (EAST);
// 	}
// 	else
// 	{
// 		if (dy > 0)
// 			return (NORTH);
// 		else
// 			return (SOUTH);
// 	}
// }
//

void	put_game(t_game *game)
{
	float		fov = 45;
	float		i;
	t_player	 player;
	float		h;
	float		s;
	t_point		start;
	t_point		stop;
	float		dist;
	t_dist		hit;
	float		step;
	int			j;
	t_point		temp_s;
	t_point		temp_e;

	i = -(fov / 2);
	player = game->player;
	step = fov / WIDTH;
	put_bg(game, game->text.c_color.rgb_hex, game->text.f_color.rgb_hex);
	put_map(game);
	while (i < fov / 2)
	{	
		hit = find_hit(player.dir_x + i, player.x, player.y);
		dist = distance(player.x, player.y, hit.hit, i);
		h = (40 / dist) * (WIDTH / 3.7f);
		ft_texture(game->game_t, player.x + game->minimap.x, player.y + game->minimap.y, 0x000000);
		drawline(game->game_t, (t_point){0x0000FF, player.x + game->minimap.x, player.y + game->minimap.y, 0}, (t_point){0x0000FF, hit.hit.x + game->minimap.x, hit.hit.y + game->minimap.y, 0});
		// hit.side = set_side_wall(hit);
		s = (HEIGHT - h) / 2;
		start.color = set_wall_color(hit);
		start.outcode = 0;
		stop.color = set_wall_color(hit);
		stop.outcode = 0;
		start.py = s + (player.z * 30 / dist) + player.dir_y;
		stop.py = h + s + (player.z * 30 / dist) + player.dir_y;
		// if (!hit.ishit)
		// {
		// 	// put_smoke(game, i, fov);
		// 	i += step;
		// 	continue ;
		// }
		start.color = apply_fog(start.color, dist, 120);
		stop.color = apply_fog(stop.color, dist, 120);
		j = 0;
		while (j < 4)
		{
			start.px = ((float)WIDTH / 2) + i * fov + j;
			stop.px = ((float)WIDTH / 2) + i * fov + j;
			drawline(game->game_t, start, stop);
			j++;
		}
		temp_s.px = start.px;
		temp_s.py = start.py;
		temp_s.color = start.color;
		temp_s.outcode = 0;
		temp_e.px = stop.px;
		temp_e.py = stop.py;
		temp_e.color = stop.color;
		temp_e.outcode = 0;
		i += step;
	}
}
