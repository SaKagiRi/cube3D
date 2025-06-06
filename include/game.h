/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:26:31 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 23:17:47 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GAME_H
# define GAME_H

# include "MLX42.h"
# include "kml.h"
# include "map.h"
# include <stdio.h>
# include <unistd.h>

# define PI 3.14159

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

typedef struct s_mlx
{
}	t_mlx;

/**
 * @brief Player information
 */
typedef struct s_player
{
	float	dir;
	float	x;
	float	y;
}	t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player	player;
	t_map		map;
	t_text		text;
	t_err		err;
	bool		on_change;
	bool		first_render;
	float		player_speed;
	int			player_size;
	int			move_cam_speed;
	int			scale;
}	t_game;

t_game	*get_game(void);

#endif
