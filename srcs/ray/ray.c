/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:20:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/11 18:16:58 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "../../include/cube.h"
#include "game.h"
#include <math.h>
#include <stdlib.h>

float	distance(float px, float py, t_vec2 hit)
{
	float	dis;

	float dx = hit.x - px;
	float dy = hit.y - py;
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}

t_vec2	find_hit(float ray_angle, float x, float y)
{
	t_vec2	cur;
	t_vec2	temp;
	float	r;
	t_tile	**map;
	float	scale;
	float	rad;

	r = 0;
	map = get_game()->map.map;
	scale = get_game()->scale;
	rad = ray_angle * PI / 180;
	cur.x = x;
	cur.y = y;
	while (r <= 5 * scale)
	// while (r >= 0)
	{
		temp.x = cur.x;
		temp.y = cur.y;
		cur.x = x + r * cos(rad);
		cur.y = y + r * sin(rad);
		if (map[(int)(cur.y / scale)][(int)(temp.x / scale)].type == WALL \
&& map[(int)(temp.y / scale)][(int)(cur.x / scale)].type == WALL)
			return (temp);
		if (map[(int)(cur.y / scale)][(int)(cur.x / scale)].type == WALL)
			return (cur);
		r += 0.1;
	}
	return (cur);
}

// void	putray(mlx_texture_t *text)
// {
// 	t_vec2		hit;
// 	t_player	player;
// 	t_player	minimap;
// 	float		rad;
// 	float		i;
//
// 	player = get_game()->player;
// 	minimap = get_game()->minimap;
// 	rad = player.dir * PI / 180;
// 	hit = find_hit(rad + 0.4, player.x, player.y);
// 	drawline(text, (t_point){0x000000, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0x000000, hit.x + minimap.x, hit.y + minimap.y, 0});
// 	hit = find_hit(rad - 0.4, player.x, player.y);
// 	drawline(text, (t_point){0x000000, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0x000000, hit.x + minimap.x, hit.y + minimap.y, 0});
// 	printf("->>%f\n", distance(player, 0));
// 	i = -0.39;
// 	while (i < 0.39)
// 	{
// 		hit = find_hit(rad + i, player.x, player.y);
// 		// if ((int)(hit.x) % get_game()->scale == 0 && (int)(hit.y) % get_game()->scale == 0)
// 		// 	drawline(text, (t_point){0xFF0000, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0xFF0000 , hit.x + minimap.x, hit.y + minimap.y, 0});
// 		// else
// 			drawline(text, (t_point){0xFF0000, player.x + minimap.x, player.y + minimap.y, 0}, (t_point){0xFF0000, hit.x + minimap.x, hit.y + minimap.y, 0});
// 		i += 0.001;
// 	}
// }

// int	findhit(t_vec2 *hit, t_player player, float ray_angle)
// {
// 	float		rad;
// 	float		x;
// 	float		y;
// 	float		r;
// 	int			scale;
// 	t_tile		**map;
//
// 	rad = (ray_angle + 90) * PI / 180;
// 	r = 0;
// 	scale = get_game()->scale;
// 	map = get_game()->map.map;
// 	while (r < 100)
// 	{
// 		player.x += r * sin(rad);
// 		player.y -= r * cos(rad);
// 		x = (int)player.x % scale;
// 		y = (int)player.y % scale;
// 		if (player.x / scale < get_game()->map.row || player.x / scale > get_game()->map.row || player.y / scale > get_game()->map.col || player.y / scale < get_game()->map.col)
// 		{
// 			hit->x = player.x;
// 			hit->y = player.y;
// 			return (-1);
// 		}
// 		if (x == scale || x == 0 || y == scale || y == 0)
// 		{
// // 		if (map[(int)(cur.y / scale)][(int)(temp.x / scale)].type == WALL \
// // && map[(int)(temp.y / scale)][(int)(cur.x / scale)].type == WALL)
// 			if (map[(int)player.y / scale][(int)player.x / scale].type == WALL)
// 			{
// 				hit->x = player.x;
// 				hit->y = player.y;
// 			}
// 			if (x == scale || x == 0)
// 				return (1);
// 			else if (y == scale || y == 0)
// 				return (2);
// 		}
// 		r += 1;
// 	}
// 	return (0);
// }

// t_vec2  findhit(t_player *player, float ray_angle) {
//     t_vec2  ray_dir;
//     t_vec2  ray_pos;
//     t_vec2  delta_dist;
//     t_vec2  side_dist;
//     int     step_x, step_y;
//     int     hit = 0;
//     int     side; // 0=แนวตั้ง, 1=แนวนอน
//
//     // คำนวณทิศทาง ray (ray_dir)
//     ray_dir.x = cos(ray_angle);
//     ray_dir.y = sin(ray_angle);
//
//     // ตั้งค่าเริ่มต้น (DDA Algorithm)
//     ray_pos.x = player->x;
//     ray_pos.y = player->y;
//
//     // คำนวณระยะทางระหว่างกริด (deltaDist)
//     delta_dist.x = (ray_dir.x == 0) ? 1e30 : fabs(1 / ray_dir.x);
//     delta_dist.y = (ray_dir.y == 0) ? 1e30 : fabs(1 / ray_dir.y);
//
//     // คำนวณทิศทางการก้าว (step) และระยะเริ่มต้น (sideDist)
//     if (ray_dir.x < 0) {
//         step_x = -1;
//         side_dist.x = (player->x - ray_pos.x) * delta_dist.x;
//     } else {
//         step_x = 1;
//         side_dist.x = (ray_pos.x + 1.0 - player->x) * delta_dist.x;
//     }
//     if (ray_dir.y < 0) {
//         step_y = -1;
//         side_dist.y = (player->y - ray_pos.y) * delta_dist.y;
//     } else {
//         step_y = 1;
//         side_dist.y = (ray_pos.y + 1.0 - player->y) * delta_dist.y;
//     }
//
//     // DDA Loop
//     while (!hit) {
//         if (side_dist.x < side_dist.y) {
//             side_dist.x += delta_dist.x;
//             ray_pos.x += step_x;
//             side = 0;
//         } else {
//             side_dist.y += delta_dist.y;
//             ray_pos.y += step_y;
//             side = 1;
//         }
//         // ตรวจสอบว่าชนกำแพง (ใช้ map[y][x])
// 		t_tile	**map;
//
// 		map = get_game()->map.map;
//         if (map[(int)ray_pos.y][(int)ray_pos.x].type == WALL)
//             hit = 1;
//     }
//
// 	(void)side;
//     // คืนค่าตำแหน่งที่ชน (hit position)
//     return (ray_pos);
// }
