/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:24:23 by lucas             #+#    #+#             */
/*   Updated: 2023/03/30 01:36:28 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *r)
{
	if (r->dir_char == 'N')
		r->dir[X] = -1;
	else if (r->dir_char == 'S')
		r->dir[X] = 1;
	else if (r->dir_char == 'E')
		r->dir[Y] = 1;
	else if (r->dir_char == 'W')
		r->dir[Y] = -1;
	r->plane[X] = 0.66 * r->dir[Y];
	r->plane[Y] = -0.66 * r->dir[X];
	r->speed = 0.1;
}

void	ft_mlx_init_img(t_view *view)
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
	init_ray(&data->ray);
	handles_all_hooks(data);
}
