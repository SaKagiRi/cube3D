/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:23:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/19 03:57:53 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "cube.h"
#include "drawline.h"
#include "map.h"
#include "unistd.h"

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
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;

    // สีหมอก (0x646464)
    uint8_t fog_r = 0x30;
    uint8_t fog_g = 0x30;
    uint8_t fog_b = 0x30;

    // ผสมสี
    uint8_t new_r = r * (1.0f - fog_intensity) + fog_r * fog_intensity;
    uint8_t new_g = g * (1.0f - fog_intensity) + fog_g * fog_intensity;
    uint8_t new_b = b * (1.0f - fog_intensity) + fog_b * fog_intensity;

    return ((new_r << 24) | (new_g << 16) | (new_b << 8) | 0xFF);
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



	center_x = (hit.block.x * SCALE) + (SCALE / 2.0f);
	center_y = (hit.block.y * SCALE) + (SCALE / 2.0f);
	// printf("->>%f, %f\n", center_x, center_y);

	ft_texture(get_game()->game_t, center_x + get_game()->minimap.x, center_y + get_game()->minimap.y, 0xFF0000);
	//
	// if (hit.block.x == 0 && hit.block.y == 0)
	// 	return (-1);
	// center_x = (hit.block.x * SCALE) + (SCALE / 2.0f);
	// center_y = (hit.block.y * SCALE) + (SCALE / 2.0f);
	// // printf("cx:%f, cy:%f\n, hx:%f, hy:%f\n\n\n", center_x, center_y, hit.hit.x, hit.hit.y);
	// return (get_block_side(center_x, center_y, hit.hit.x, hit.hit.y));
	return (hit.side);
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


t_vec2	get_gap(t_game *game, t_vec2 hit)
{
	t_vec2		gap;

	gap.x = 0;
	gap.y = 0;
	while (hit.y - gap.y > 0 && hit.y - gap.y < game->map.row * SCALE)
	{
		ft_texture(game->game_t, hit.x + game->minimap.x, hit.y - gap.y + game->minimap.y, 0xFF0000FF);
		if ((int)(hit.y - gap.y) % 10 == 0)
			break ;
		gap.y += 0.01;
	}
	while (hit.x - gap.x > 0 && hit.x - gap.x < game->map.col * SCALE)
	{
		ft_texture(game->game_t, hit.x - gap.x + game->minimap.x, hit.y + game->minimap.y, 0xFF0000FF);
		if ((int)(hit.x - gap.x) % 10 == 0)
			break ;
		gap.x += 0.01;
	}
	return (gap);
}

void	set_background(t_game *game)
{
	if (game->fog)
		put_bg_fog(game, game->text.c_color.rgb_hex, game->text.f_color.rgb_hex);
	else
		put_bg(game, game->text.c_color.rgb_hex, game->text.f_color.rgb_hex);
}

void	fill_line_wall(float x, float s_y, float e_y, t_dist hit)
{
	t_game	*game;
	size_t	rgba;
	int		i;
	int		k;
	static int		j = 0;
	float	scale;
	t_vec2	gap;


	i = 0;
	game = get_game();
	gap = get_gap(game, hit.hit);
	scale = (float)SCALE / game->text.e_txt->width;
	// j = (game->text.e_txt->width / scale) * gap.x;
	k = 0;
	if (j > (int)game->text.e_txt->width)
		j = 0;
	while (s_y + i < e_y)
	{
		ft_texture_color(game->text.e_txt, k, j, &rgba);
		ft_texture(game->game_t, x, s_y + i, rgba);
		if (k > (int)game->text.e_txt->height)
			k = 0;
		i++;
		k++;
	}
	j++;
	(void)gap;
	(void)scale;
}

void	set_wall(t_game *game, t_player player, float ray_angle)
{
	t_dist		hit;
	float		dist;
	float		height;
	float		start;
	float		stop;
	float		x;

	hit = find_hit(player.dir_x + ray_angle, player.x, player.y);
	dist = distance(player.x, player.y, hit.hit, ray_angle);
	if (dist < 2)
		dist = 2;
	hit.side = set_side_wall(hit);
	height = (40 / dist) * (WIDTH / 3.7f);
	start = ((HEIGHT - height) / 2);
	stop = height + start + (player.z * 30 / dist) + player.dir_y;
	start += (player.z * 30 / dist) + player.dir_y; 
	x = ((float)WIDTH / 2) + ray_angle * (WIDTH / game->fov);
	fill_line_wall(x, start, stop, hit);
	
}

void	put_game(t_game *game)
{
	float		ray_angle;
	t_player	player;
	float		step;

	ray_angle = -(game->fov / 2);
	player = game->player;
	step = game->fov / WIDTH;
	while (ray_angle < game->fov / 2)
	{	
		set_wall(game, player, ray_angle);
		// ft_texture(game->game_t, player.x + game->minimap.x, player.y + game->minimap.y, 0x000000);
		// drawline(game->game_t, (t_point){0x0000FF, player.x + game->minimap.x, player.y + game->minimap.y, 0}, (t_point){0x0000FF, hit.hit.x + game->minimap.x, hit.hit.y + game->minimap.y, 0});
		
		//
		// start.color = set_wall_color(hit);
		// start.outcode = 0;
		// stop.color = set_wall_color(hit);
		// stop.outcode = 0;
		// start.py = s + (player.z * 30 / dist) + player.dir_y;
		// stop.py = h + s + (player.z * 30 / dist) + player.dir_y;

		// start.color = apply_fog(start.color, dist, 120);
		// stop.color = apply_fog(stop.color, dist, 120);
		// start.px = ((float)WIDTH / 2) + ray_angle * (WIDTH / fov);
		// stop.px = ((float)WIDTH / 2) + ray_angle * (WIDTH / fov);
		// drawline(game->game_t, start, stop);
		ray_angle += step;
	}
	// ft_texture(game->game_t, 0, 0, 0xFAAFAAFF);
	// printf("before:%ld", (long)0xFAAFAAFF);
	// c = 0;
	// ft_texture_color(game->game_t, 0, 0, &c);
	// printf("after:%ld\n", c);
}
