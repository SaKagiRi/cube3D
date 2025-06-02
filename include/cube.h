/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:29 by knakto            #+#    #+#             */
/*   Updated: 2025/06/02 23:55:47 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include <unistd.h>

# include "kml.h"
# include "MLX42.h"

# ifndef LIMIT_MAP_SIZE
#  define LIMIT_MAP_SIZE 100
# endif

/**
 * 
 * @brief List of error numeration for debugging error
 * 
 * - `ARG` - Arguments error.
 * 
 * - `FILE` - Error from file (such as permission denied, no such file).
 * 
 * - `MAP` - Content in map doesn't fulfill condition.
 * 
 * - `MEM` - Error from allocation.
 * 
 */
typedef enum e_err
{
	OK,
	ARG,
	FILE,
	MAP,
	MEM
}	t_err;

/**
 * @brief color is compose of 4 byte of color each has 8 bit.
 * 
 * struct {
 *
 * - unsigned char `a` - alpha value (opacity).
 *
 * - unsigned char `b` - blue value.
 * 
 * - unsigned char `g` - green value.
 * 
 * - unsigned char `r` - red value.
 * 
 * }
 * 
 * - unsigned char `rgba[4]` - array of each byte of color
 * 
 * - unsigned int `rgb_hex` - value of combine every bit into ul.
 * 
 */
typedef union u_color
{
	struct
	{
		unsigned char	a;
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
	};
	unsigned char	rgba[4];
	unsigned int	rgb_hex;
}	t_color;

/**
 * 
 * - mlx_texture_t `n_txt` - North texture.
 * 
 * - mlx_texture_t `e_txt` - East texture.
 * 
 * - mlx_texture_t `s_txt` - South texture.
 * 
 * - mlx_texture_t `w_txt` - West texture.
 * 
 * - t_color `f_color` - Floor color.
 * 
 * - t_color `c_color` - Ceil color.
 * 
 */
typedef struct s_map
{
	unsigned int	width;
	unsigned int	length;
	char			**map;
	mlx_texture_t	n_txt;
	mlx_texture_t	e_txt;
	mlx_texture_t	s_txt;
	mlx_texture_t	w_txt;
	t_color			f_color;
	t_color			c_color;
}	t_map;

/**
 * @brief Player information
 */
typedef struct s_player
{
	int	pos;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_player	player;
	t_map		map;
	t_err		err;
}	t_game;

int		in(char c, char	*set);
t_err	walloc(void *arg, size_t size);

t_game	*get_game(void);

void	keyhook(void *arg);

#endif
