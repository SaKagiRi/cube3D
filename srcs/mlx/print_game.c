/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:37:04 by knakto            #+#    #+#             */
/*   Updated: 2025/06/09 01:36:46 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "game.h"
#include "drawline.h"
#include "map.h"
#include "ray.h"

// void	put_game(mlx_texture_t *text)
// {
// 	t_game	*game;
// 	t_vec2	hit;
// 	float	dis;
// 	float	rad;
// 	int	wallheight;
// 	float	mid_x;
// 	float	mid_y;
// 	float	i;
// 	// float corrected_angle;
//
// 	game = get_game();
// 	rad = (game->player.dir) * PI / 180;
// 	mid_x = (int)(WIDTH / 2);
// 	mid_y = (int)(HEIGHT / 2);
// 	i = -39;
// 	while (i < 39)
// 	{
// 		hit = find_hit(rad + (i / 10), game->player.x, game->player.y);
// 		// corrected_angle = rad + (i / 10) - game->player.dir;
// 		dis = distance(game->player.x, game->player.y, hit.x, hit.y);
// 		dis = dis * cos(rad + (i / 10) - rad);
// 		// dis *= cos(corrected_angle * PI / 180.0);
// 		// printf("--%f\n", dis);
// 		if (dis <= 49)
// 		{
// 			wallheight = (HEIGHT / dis) / 2;
// 			// ft_texture(text, mid_x, mid_y, 0xFF0000);
// 			// (void)wallheight;
// 			bresenham(text, (t_point){0xFF0000, mid_x + i, mid_y - wallheight, 0}, (t_point){0xFF0000, mid_x + i, mid_y + wallheight, 0});
// 		}
// 		i++;
// 	}
// 	// game->game_i = mlx_texture_to_image(game->mlx, text);
// 	// mlx_image_to_window(game->mlx, game->game_i, 0, 0);
// 	// mlx_delete_texture(text);
// }

void	put_game(mlx_texture_t *text)
{
	t_game	*game;
	t_vec2	hit;
	float	dis;
	float	angle_offset;
	float	ray_angle;
	int		wallheight;
	float	mid_x = (int)(WIDTH / 2);
	float	mid_y = (int)(HEIGHT / 2);
	float	i;

	game = get_game();
	float player_rad = game->player.dir * PI / 180.0f;
	i = -150;
	while (i < 150)
	{
		angle_offset = (i / 10.0f) * (PI / 180.0f); // degree to rad
		ray_angle = player_rad + angle_offset;

		hit = find_hit(ray_angle, game->player.x, game->player.y);
		dis = distance(game->player.x, game->player.y, hit.x, hit.y);

		dis *= cos(angle_offset); // fish-eye correction

		if (dis <= 50)
		{
			wallheight = (HEIGHT / dis) / 2;
			bresenham(text,
				(t_point){0xFF0000, mid_x + i, mid_y - wallheight, 0},
				(t_point){0xFF0000, mid_x + i, mid_y + wallheight, 0});
		}
		i++;
	}
}

