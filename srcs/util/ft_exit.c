/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:06:52 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/15 05:14:01 by kawaii           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	msg_set1(t_err error)
{
	if (error == OK)
		ft_putstr_fd("Exit Successful", 2);
	else if (error == ARG_ERR)
		ft_putendl_fd("Invalid Argument Number.", 2);
	else if (error == MEM_ERR)
		ft_putendl_fd("Memory Error.", 2);
	else if (error == FILE_ERR)
		ft_putendl_fd("File Error.", 2);
	else if (error == MAP_ERR)
		ft_putendl_fd("Map content Error.", 2);
	else if (error == CHARAC_ERR)
		ft_putendl_fd("Character not found or too many character.", 2);
	else if (error == OVR_LM)
		ft_putendl_fd("Map size is over the limit.", 2);
	else if (error == ATTR_ERR)
		ft_putendl_fd("Map texture or color attribute error.", 2);
	else if (error == WALL_ERR)
		ft_putendl_fd("Map doesn't close properly.", 2);
	else
		ft_putendl_fd("Unexpected or Unrecord Error.", 2);
}

void	clear_texture(t_text *text)
{
	if (text->n_txt)
		mlx_delete_texture(text->n_txt);
	if (text->e_txt)
		mlx_delete_texture(text->e_txt);
	if (text->w_txt)
		mlx_delete_texture(text->w_txt);
	if (text->s_txt)
		mlx_delete_texture(text->s_txt);
}

// only use this when there's still buffer left in buffer
void	clear_get_next_line(t_map *map, int fd)
{
	while (map->buf)
	{
		free(map->buf);
		map->buf = get_next_line(fd);
	}
	close(fd);
}

void	ft_exit(int n)
{
	t_err	err;

	err = get_game()->err;
	msg_set1(err);
	exit(n);
}
