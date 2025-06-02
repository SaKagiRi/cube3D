/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:01 by knakto            #+#    #+#             */
/*   Updated: 2025/06/02 14:16:58 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(void)
{
	mlx_t		*mlx;

	mlx = mlx_init(1920, 1080, "Cube3D", true);
	if (!mlx)
		return (1);
	mlx_loop_hook(mlx, keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
