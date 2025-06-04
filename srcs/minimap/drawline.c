/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:21:06 by knakto            #+#    #+#             */
/*   Updated: 2025/06/04 15:28:16 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

static void	mirror(int *diff, int *inc)
{
	if (*diff < 0)
	{
		*inc = -1;
		*diff = -*diff;
	}
}

static void	x_line(mlx_texture_t *texture, t_point *start, t_point *stop)
{
	int		dx;
	int		dy;
	int		inc;
	int		diff;
	t_point	pos;

	inc = 1;
	dx = stop->px - start->px;
	dy = stop->py - start->py;
	mirror(&dy, &inc);
	diff = (2 * dy) - dx;
	pos = *start;
	while (pos.px < stop-> px)
	{
		if (pos.px > 0 && pos.py > 0 && pos.px < WIDTH && pos.py < HEIGHT)
			ft_texture(texture, pos.px, pos.py, 0x000000);
		if (diff > 0)
		{
			pos.py += inc;
			diff += 2 * (dy - dx);
		}
		else
			diff += 2 * dy;
		pos.px++;
	}
}

static void	y_line(mlx_texture_t *texture, t_point *start, t_point *stop)
{
	int		dx;
	int		dy;
	int		inc;
	int		diff;
	t_point	pos;

	inc = 1;
	dx = stop->px - start->px;
	dy = stop->py - start->py;
	mirror(&dx, &inc);
	diff = (2 * dx) - dy;
	pos = *start;
	while (pos.py < stop->py && pos.py < HEIGHT)
	{
		if (pos.px > 0 && pos.py > 0 && pos.px < WIDTH && pos.py < HEIGHT)
			ft_texture(texture, pos.px, pos.py, 0x000000);
		if (diff > 0)
		{
			pos.px += inc;
			diff += 2 * (dx - dy);
		}
		else
			diff += 2 * dx;
		pos.py++;
	}
}

static int	border_bound(t_point *ori, t_point *end)
{
	if (((ori->px < 0 && end->px < 0) || (ori->px > WIDTH && end->px > WIDTH)))
		return (0);
	if ((ori->py < 0 && end->py < 0) || (ori->py > HEIGHT && end->py > HEIGHT))
		return (0);
	return (1);
}

void	bresenham(mlx_texture_t *texture, t_point start, t_point stop)
{
	cohen(&start, &stop);
	if (!border_bound(&start, &stop))
		return ;
	if (ft_abs(stop.py - start.py) < ft_abs(stop.px - start.px))
	{
		if (start.px > stop.px)
			x_line(texture, &stop, &start);
		else
			x_line(texture, &start, &stop);
	}
	else
	{
		if (start.py > stop.py)
			y_line(texture, &stop, &start);
		else
			y_line(texture, &start, &stop);
	}
}

