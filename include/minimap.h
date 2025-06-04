/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:04:12 by knakto            #+#    #+#             */
/*   Updated: 2025/06/04 15:32:54 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "kml.h"
# include "MLX42.h"

typedef enum e_type_map
{
	WALL,
	FLOOR,
	VOID,
	PLAYER,
}	t_type_map;

typedef struct s_player_pos
{
	int		dir;
	float	x;
	float	y;
}	t_player_pos;

typedef struct s_map_pos
{
	int			x;
	int			y;
	int			type;
}	t_map_pos;

typedef struct s_point
{
	long		color;
	float		px;
	float		py;
	char		outcode;
}	t_point;

t_player_pos	*get_t_player(void);
t_map_pos	****get_t_map(void);
void	addmap(char	*map);
void	print(void);

//texture
mlx_texture_t	*new_texture(size_t w, size_t h, size_t bg_color);
void			fill_background(mlx_texture_t *texture, size_t color);
int				ft_texture(mlx_texture_t *texture, float x, float y, size_t rgb);
void	bresenham(mlx_texture_t *texture, t_point start, t_point stop);

//cohen
void	cohen(t_point *s1, t_point *s2);
float	ft_abs(float a);

#endif
