/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:26:31 by knakto            #+#    #+#             */
/*   Updated: 2025/06/22 20:17:28 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GAME_H
# define GAME_H

# include "kml.h"
# include "MLX42.h"
# include "drawline.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>

# define PI 3.14159

# ifndef WIDTH
#  define WIDTH 1500
# endif

# ifndef HEIGHT
#  define HEIGHT 900
# endif

# ifndef MINI_WIDTH
#  define MINI_WIDTH 200
# endif

# ifndef MINI_HEIGHT
#  define MINI_HEIGHT 150
# endif

# ifndef SCALE
#  define SCALE 10
# endif

typedef enum e_type
{
	END,
	EMPT,
	U_PATH,
	PATH,
	WALL,
}	t_type;

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
	MEM_ERR,
	ARG_ERR,
	FILE_ERR,
	ATTR_ERR,
	MAP_ERR,
	WALL_ERR,
	CHARAC_ERR,
	OVR_LM
}	t_err;

typedef enum e_rmode
{
	ATTR_M,
	MAP_M
}	t_rmode;

/**
 * @brief List storing content raw string read from map
 */
typedef struct s_mapvec
{
	t_list	*raw_map;
	t_list	*cur_row;
}	t_mapvec;

typedef struct s_tile
{
	int		x;
	int		y;
	t_type	type;
}	t_tile;

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

typedef struct s_text
{
	int				set;
	mlx_texture_t	*n_txt;
	mlx_texture_t	*e_txt;
	mlx_texture_t	*s_txt;
	mlx_texture_t	*w_txt;
	t_color			f_color;
	t_color			c_color;
}	t_text;

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
	t_rmode			mode;
	bool			p_init;
	int				map_fd;
	int				col;
	int				row;
	char			*buf;
	t_mapvec		vecmap;
	t_tile			**map;
}	t_map;

mlx_texture_t	*new_texture(size_t w, size_t h, size_t bg_color);
void			fill_background(mlx_texture_t *texture, size_t bg_color);
int				ft_texture(mlx_texture_t *texture, float x, float y, size_t rgb);
int	ft_texture_color(mlx_texture_t *texture, \
size_t x, size_t y, size_t *color);

typedef struct s_mlx
{
}	t_mlx;

/**
 * @brief Player information
 */
typedef struct s_player
{
	float	dir_x;
	float	dir_y;
	float	z;
	float	x;
	float	y;
	char	outcode;
}	t_player;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*game_i;
	mlx_texture_t	*game_t;
	t_player	player;
	t_player	minimap;
	t_map		map;
	t_text		text;
	t_err		err;
	bool		on_change;
	bool		first_render;
	bool		on_jump;
	bool		fog;
	int			mouse;
	float		fov;
	float		mouse_sen;
	float		player_speed;
	int			player_size;
	int			move_cam_speed;
	int			scale;
}	t_game;

t_game	*get_game(void);

#endif
