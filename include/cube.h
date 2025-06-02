/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:29 by knakto            #+#    #+#             */
/*   Updated: 2025/06/02 14:43:24 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "kml.h"
# include "MLX42.h"

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
 * 
 * 
 */
typedef struct	s_texture
{
	mlx_texture_t	n_txt;
	mlx_texture_t	e_txt;
	mlx_texture_t	s_txt;
	mlx_texture_t	w_txt;
}	t_texture;

void	keyhook(void *arg);

#endif
