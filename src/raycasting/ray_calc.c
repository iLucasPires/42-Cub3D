/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:12 by lucas             #+#    #+#             */
/*   Updated: 2023/03/21 14:59:23 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		worldMap5[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void	calc_camera(t_ray *ray, int pixel)
{
	double	multiplier;

	multiplier = 2 * pixel / (double)WIDTH - 1;
	ray->ray_dir[X] = ray->dir[X] + ray->plane[X] * multiplier;
	ray->ray_dir[Y] = ray->dir[Y] + ray->plane[Y] * multiplier;
}

void	calc_delta(t_ray *r)
{
	r->wall_pos[X] = (int)r->pos[X];
	r->wall_pos[Y] = (int)r->pos[Y];
	if (r->ray_dir[X] == 0)
	{
		r->delta[X] = 1;
		r->delta[Y] = 0;
	}
	if (r->ray_dir[Y] == 0)
	{
		r->delta[X] = 0;
		r->delta[Y] = 1;
	}
	if (r->ray_dir[X] != 0 && r->ray_dir[Y] != 0)
	{
		r->delta[X] = fabs(1 / r->ray_dir[X]);
		r->delta[Y] = fabs(1 / r->ray_dir[Y]);
	}
}

void	calc_side_x(t_ray *r)
{
	if (r->ray_dir[X] < 0)
	{
		r->dist_to_side[X] = (r->pos[X] - r->wall_pos[X]) * r->delta[X];
		r->step[X] = -1;
	}
	else
	{
		r->dist_to_side[X] = (r->wall_pos[X] + 1.0 - r->pos[X]) * r->delta[X];
		r->step[X] = 1;
	}
}

void	calc_side_y(t_ray *r)
{
	if (r->ray_dir[Y] < 0)
	{
		r->dist_to_side[Y] = (r->pos[Y] - r->wall_pos[Y]) * r->delta[Y];
		r->step[Y] = -1;
	}
	else
	{
		r->dist_to_side[Y] = (r->wall_pos[Y] + 1.0 - r->pos[Y]) * r->delta[Y];
		r->step[Y] = 1;
	}
}

void	calc_dda(t_ray *r, t_view *v)
{
	r->dda_line_size[X] = r->dist_to_side[X];
	r->dda_line_size[Y] = r->dist_to_side[Y];
	while (true)
	{
		if (r->dda_line_size[X] < r->dda_line_size[Y])
		{
			r->wall_pos[X] += r->step[X];
			r->dda_line_size[X] += r->delta[X];
			r->hit_side = false;
		}
		else
		{
			r->wall_pos[Y] += r->step[Y];
			r->dda_line_size[Y] += r->delta[Y];
			r->hit_side = true;
		}
		if (worldMap5[r->wall_pos[X]][r->wall_pos[Y]] > 0)
			break ;
	}
}

void	calc_perpendicular(t_ray *ray)
{
	if (ray->hit_side == false)
	{
		ray->wall_dist[X] = (ray->wall_pos[X] - ray->pos[X]) + (1 - ray->step[X]) / 2;
		ray->perpendicular = fabs(ray->wall_dist[X] / ray->ray_dir[X]);
	}
	else
	{
		ray->wall_dist[Y] = (ray->wall_pos[Y] - ray->pos[Y]) + (1- ray->step[Y]) / 2;
		ray->perpendicular = fabs(ray->wall_dist[Y] / ray->ray_dir[Y]);
	}
	ray->line_size[0] = HEIGHT / 2 - (HEIGHT / ray->perpendicular) / 2;
	ray->line_size[1] = HEIGHT / 2 + (HEIGHT / ray->perpendicular) / 2;
}