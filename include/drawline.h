/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:00:04 by knakto            #+#    #+#             */
/*   Updated: 2025/06/06 02:08:22 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWLINE_H
# define DRAWLINE_H

# include "MLX42.h"

typedef struct s_point
{
	long		color;
	float		px;
	float		py;
	char		outcode;
}	t_point;

void	cohen(t_point *s1, t_point *s2);
void	bresenham(mlx_texture_t *text, t_point start, t_point stop);

#endif
