/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:39:00 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/02 15:00:18 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

/**
 * @name Keyhook & Event
 * 
 * utility function for hook of key and events of the game.
 * @{
 * 
 */

/**
 * @brief Keyhook funtion
 *
 *
 * @retval 
 *
 */
void	keyhook(void *arg)
{
	mlx_t	*mlx;

	mlx = arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		printf("Esc\n");
		// mlx_terminate(mlx);
}

// static void	reset_prop(t_prop *prop)
// {
// 	prop->tran_x = WIDTH / 2;
// 	prop->tran_y = HEIGHT / 2;
// 	prop->x_deg = 2;
// 	prop->y_deg = 0;
// 	prop->z_deg = 45;
// 	prop->scale = FIX_SCALE;
// }

// void	reframe(t_fdf *fdf, t_prop *prop, t_map *map)
// {
// 	t_2axis	pos;

// 	pos.y = 0;
// 	while (pos.y < HEIGHT)
// 	{
// 		pos.x = 0;
// 		while (pos.x < WIDTH)
// 		{
// 			mlx_put_pixel(fdf->img, pos.x, pos.y, 0xFF);
// 			pos.x++;
// 		}
// 		pos.y++;
// 	}
// 	render(fdf, prop, map);
// }

// void	change_projection(void *param)
// {
// 	t_fdf	*fdf;
// 	t_prop	*prop;

// 	fdf = param;
// 	prop = &fdf->prop;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
// 		prop->mode = ISO;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
// 		prop->mode = OTH_T;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
// 		prop->mode = OTH_F;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_4))
// 		prop->mode = OTH_S;
// }

// void	transform(void *param)
// {
// 	t_fdf	*fdf;
// 	t_prop	*prop;

// 	fdf = param;
// 	prop = &fdf->prop;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
// 		prop->tran_y += abs(WIDTH / prop->scale);
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
// 		prop->tran_y -= abs(WIDTH / prop->scale);
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
// 		prop->tran_x -= abs(WIDTH / prop->scale);
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
// 		prop->tran_x += abs(WIDTH / prop->scale);
// }

// void	move_control(void *param)
// {
// 	t_fdf	*fdf;
// 	t_prop	*prop;

// 	fdf = param;
// 	prop = &fdf->prop;
// 	transform(param);
// 	change_projection(param);
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(fdf->mlx);
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E) && prop->mode == ISO)
// 		prop->z_deg = (int)(prop->z_deg - 1) % 360;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q) && prop->mode == ISO)
// 		prop->z_deg = (int)(prop->z_deg + 1) % 360;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z) && prop->scale < 500)
// 		prop->scale++;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_C) && prop->scale > 1)
// 		prop->scale--;
// 	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
// 		reset_prop(prop);
// 	reframe(fdf, prop, prop->map);
// }

/**
 * @}
 */
