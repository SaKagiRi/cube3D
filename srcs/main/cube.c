/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:01 by knakto            #+#    #+#             */
/*   Updated: 2025/06/02 13:38:16 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(void)
{
	mlx_t		*mlx;

	mlx = mlx_init(1920, 1080, "Cube3D", true);
	if (!mlx)
		return (1);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
