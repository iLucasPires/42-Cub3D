/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:24:23 by lucas             #+#    #+#             */
/*   Updated: 2023/03/28 20:15:50 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void 	ft_mlx_init_img(t_view	*view)
{
	view->screen.img = mlx_new_image(view->mlx, WIDTH, HEIGHT);
	view->screen.addr = ft_mlx_get_addr(&view->screen);
}

void	ft_mlx_init(t_data *data)
{
	t_view	*view;

	view = &data->view;
	view->mlx = mlx_init();
	view->win = mlx_new_window(view->mlx, WIDTH, HEIGHT, TITLE);
	ft_mlx_init_img(view);
	handles_all_hooks(data);
}
