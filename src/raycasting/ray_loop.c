/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:04:51 by rlins             #+#    #+#             */
/*   Updated: 2023/04/03 10:45:42 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y);

void	calc_raycast(t_data *data)
{
	int	pixel;

	pixel = 0;
	while (pixel < WIDTH)
	{
		setup_raycast_info(pixel, &data->ray, &data->player);
		calc_dda(&data->ray, &data->player);
		perform_dda(data, &data->ray);
		calculate_line_height(&data->ray, &data->player);
		update_text_pixels(data, &data->texture_det, &data->ray, pixel);
		pixel++;
	}
	if (DEBUG_INFO)
		debug(data);
}

/**
 * @brief Responsible to read all pixel by pixel and draw the screen.
 * The first condition will draw the textures.
 * The second condition will draw the Ceiling/sky
 * The third condition will draw the floor/ground
 * @hint: If we go to implement the map, probably, the call will be here!
 * @param data Data Structure
 * @param image Image structure
 * @param x x coordinate in map array
 * @param y y coordinate in map array
 */
static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < HEIGHT / 2)
		set_image_pixel(image, x, y, data->texture_det.hex_ceiling);
	else if (y < HEIGHT -1)
		set_image_pixel(image, x, y, data->texture_det.hex_floor);
}

/**
 * @brief pass through all pixel
 *
 * @hint: mlx_put_image_to_window is the responsible to put image in screen.
 * If reallocated inside the loop, all draw will be slow / you can see the
 * screen generating...
 * @param data
 */
static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->view.mlx, data->view.win, image.img, 0, 0);
	mlx_destroy_image(data->view.mlx, image.img);
}

void	render_images(t_data *data)
{
	init_texture_pixels(data);
	calc_raycast(data);
	render_frame(data);
}

int	ray_loop(t_data *data)
{
	data->player.has_moved += move_player(data);
	if (data->player.has_moved == 0)
		return (0);
	render_images(data);
	return (SUCCESS);
}
