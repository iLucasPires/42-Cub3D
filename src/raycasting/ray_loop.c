#include "cub3d.h"

void	calc_raycast(t_data *data)
{
	int	pixel;

	pixel = 0;
	while (pixel < WIDTH)
	{
		calc_camera(&data->ray, pixel);
		calc_delta(&data->ray);
		calc_side(&data->ray);
		calc_dda(&data->ray, &data->view, data->map);
		calc_perpendicular(&data->ray);
		draw_wall(data, pixel);
		pixel++;
	}
}

int	ray_loop(t_data *data)
{
	draw_ceiling(data);
	draw_floor(data);
	calc_raycast(data);
	draw_minimap(data);
	ft_mlx_put_img(&data->view, &data->view.screen, 0, 0);
	return (SUCCESS);
}
