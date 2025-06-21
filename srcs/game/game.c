/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:23:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/22 03:36:22 by knakto           ###   ########.fr       */
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
	float dx;
	float dy;

	dx = hit_x - center_x; 
	dy = hit_y - center_y;
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
	if (hit.block.x == 0 && hit.block.y == 0)
		return (-1);
	return (get_block_side(center_x, center_y, hit.hit.x, hit.hit.y));
}

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

void	set_background(t_game *game)
{
	if (game->fog)
		put_bg_fog(game, game->text.c_color.rgb_hex, game->text.f_color.rgb_hex);
	else
		put_bg(game, game->text.c_color.rgb_hex, game->text.f_color.rgb_hex);
}

mlx_texture_t	*get_side(t_game *game, int side)
{
	if (side == NORTH)
		return (game->text.n_txt);
	else if (side == WEST)
		return (game->text.w_txt);
	else if (side == EAST)
		return (game->text.e_txt);
	else if (side == SOUTH)
		return (game->text.s_txt);
	return (NULL);
}

void	fill_texture_wall(t_game *game, t_vec2 start, float height, t_dist hit)
{
	t_vec2			gap;
	t_vec2			step;
	mlx_texture_t	*text;
	int				i;
	size_t			rgba;
	
	gap = get_gap(game, hit.hit);
	step.x = gap.y / SCALE;
	if (hit.side == NORTH || hit.side == SOUTH)
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
		rgba = apply_fog(rgba, hit.dist, 9 * SCALE);
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

	hit = find_hit(player.dir_x + ray_angle, player.x, player.y);
	hit.dist = distance(player.x, player.y, hit.hit, ray_angle);
	if (hit.dist < 2)
		hit.dist = 2;
	hit.side = set_side_wall(hit);
	height = (40 / hit.dist) * (WIDTH / 3.7f);
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

	ray_angle = -(game->fov / 2);
	player = game->player;
	step = game->fov / WIDTH;
	while (ray_angle < game->fov / 2)
	{	
		set_wall(game, player, ray_angle);
		ray_angle += step;
	}
}
