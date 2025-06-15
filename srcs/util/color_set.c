/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:15:37 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/16 03:59:48 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "sys/types.h"

t_color	new_color_hex(int hex)
{
	t_color	c;

	c.rgb_hex = hex;
	return (c);
}

t_color	new_color_rgba(u_char r, u_char g, u_char b, u_char a)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}
