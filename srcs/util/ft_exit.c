/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaii <kawaii@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:06:52 by kawaii            #+#    #+#             */
/*   Updated: 2025/06/14 12:54:51 by kawaii           ###   ########.fr       */
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
	else if (error == OVR_LM \
	|| 0)
		ft_putendl_fd("Map size is over the limit.", 2);
	else
		ft_putendl_fd("Unexpected or Unrecord Error.", 2);
}

void	ft_exit(int n)
{
	t_err	err;

	err = get_game()->err;
	msg_set1(err);
	exit(n);
}
