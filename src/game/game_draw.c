/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpires-n <lpires-n@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:04:51 by rlins             #+#    #+#             */
/*   Updated: 2023/04/07 00:08:12 by lpires-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	square(t_data *d, int x, int y, int color)
{
	d->view.j = 0;
	d->view.i = 0;
	while (d->view.i < 5)
	{
		d->view.j = 0;
		while (d->view.j < 5)
		{
			set_image_pixel(&d->view.screen, x + d->view.i + 10, \
			y + d->view.j + 10, color);
			d->view.j++;
		}
		d->view.i++;
	}
	return (SUCCESS);
}

static int	minimap(t_data *d)
{
	d->view.y = 0;
	while (d->view.y < d->map_det.height)
	{
		d->view.x = 0;
		while (d->view.x < d->map_det.width)
		{
			if (d->map[d->view.y][d->view.x] == '1')
				square(d, d->view.x * 5, d->view.y * 5, COLOR_BORDER_MINIMAP);
			d->view.x++;
		}
		d->view.y++;
	}
	square(d, (d->player.pos_x * 5) - 2, \
	(d->player.pos_y * 5) - 2, COLOR_PLAYER);
	return (SUCCESS);
}

/**
 * @brief calculate the raycast for each pixel
 *
 * @param d data struct
 * @return int
 */
static int	calc_raycast(t_data *d)
{
	d->view.x = 0;
	while (d->view.x < WIDTH)
	{
		setup_raycast_info(d->view.x, &d->ray, &d->player);
		calc_dda(&d->ray, &d->player);
		perform_dda(d, &d->ray);
		calculate_line_height(&d->ray, &d->player);
		update_text_pixels(d, &d->texture_det, &d->ray, d->view.x);
		d->view.x++;
	}
	return (SUCCESS);
}

/**
 * @brief render the frame with the texture pixels
 *
 * @param d data struct
 * @return int
 */
static int	render_frame(t_data *d)
{
	d->view.y = 0;
	while (d->view.y < HEIGHT)
	{
		d->view.x = 0;
		while (d->view.x < WIDTH)
		{
			if (d->texture_pixels[d->view.y][d->view.x] > 0)
				d->view.color = d->texture_pixels[d->view.y][d->view.x];
			else if (d->view.y < HEIGHT / 2)
				d->view.color = d->texture_det.hex_ceiling;
			else if (d->view.y < HEIGHT - 1)
				d->view.color = d->texture_det.hex_floor;
			set_image_pixel(&d->view.screen, d->view.x, \
			d->view.y, d->view.color);
			d->view.x++;
		}
		d->view.y++;
	}
	return (SUCCESS);
}

int	render_images(t_data *data)
{
	init_texture_pixels(data);
	calc_raycast(data);
	render_frame(data);
	minimap(data);
	mlx_put_image_to_window(data->view.mlx, data->view.win, \
	data->view.screen.img, 0, 0);
	return (0);
}
