/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:01 by knakto            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/06/02 13:38:16 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
=======
/*   Updated: 2025/06/02 13:37:33 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"
>>>>>>> Stashed changes

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
