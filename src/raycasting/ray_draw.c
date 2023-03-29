#include "cub3d.h"


void	draw_ceiling(t_data *data)
{
	unsigned int	pixel_x;
	unsigned int	pixel_y;

	pixel_x = 0;
	while (pixel_x < WIDTH)
	{
		pixel_y = 0;
		while (pixel_y < HEIGHT)
		{
			ft_mlx_pixel_put(&data->view.screen, pixel_x, pixel_y,
				data->texture_det.hex_ceiling);
			pixel_y++;
		}
		pixel_x++;
	}
}

void	draw_floor(t_data *data)
{
	unsigned int	pixel_x;
	unsigned int	pixel_y;

	pixel_x = 0;
	while (pixel_x < WIDTH)
	{
		pixel_y = HEIGHT / 2;
		while (pixel_y < HEIGHT)
		{
			ft_mlx_pixel_put(&data->view.screen, pixel_x, pixel_y,
				data->texture_det.hex_floor);
			pixel_y++;
		}
		pixel_x++;
	}
}

void	draw_minimap_square(t_img *img, int x, int y, int color)
{
	unsigned int	pixel_x;
	unsigned int	pixel_y;

	pixel_x = 0;
	while (pixel_x < 10)
	{
		pixel_y = 0;
		while (pixel_y < 10)
		{
			ft_mlx_pixel_put(img, x * 10 + pixel_x, y * 10 + pixel_y, color);
			pixel_y++;
		}
		pixel_x++;
	}
}

void	draw_minimap(t_data *data)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < data->map_det.width)
	{
		y = 0;
		while (y < data->map_det.height)
		{
			if (data->map[y][x] == '1')
				draw_minimap_square(&data->view.screen, x, y, COLOR_MINIMAP);
			else if (data->map[y][x] == '0')
				draw_minimap_square(&data->view.screen, x, y,COLOR_BORDER_MINIMAP);
			y++;
		}
		x++;
	}
	draw_minimap_square(&data->view.screen, data->ray.pos[Y], data->ray.pos[X],
			COLOR_PLAYER);
}

void	draw_wall(t_data *data, int pixel)
{
	int	pixel_y;
	int	color;

	if (data->ray.hit_side == 0)
		color = ft_mlx_rgb_to_int(255, 0, 0);
	else
		color = ft_mlx_rgb_to_int(128, 0, 0);
	pixel_y = data->ray.line_size[0];
	while (pixel_y < data->ray.line_size[1])
	{
		ft_mlx_pixel_put(&data->view.screen, pixel, pixel_y, color);
		pixel_y++;
	}
}
