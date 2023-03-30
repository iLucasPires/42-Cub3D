/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:58:12 by lucas             #+#    #+#             */
/*   Updated: 2023/03/30 01:53:54 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_camera(t_ray *r, int pixel)
{
	r->multiplier = 2 * ((double)pixel / (double)WIDTH) - 1;
	r->ray_dir[X] = r->dir[X] + r->plane[X] * r->multiplier;
	r->ray_dir[Y] = r->dir[Y] + r->plane[Y] * r->multiplier;
}

void	calc_delta(t_ray *r)
{
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

void	calc_side(t_ray *r)
{
	if (r->ray_dir[X] < 0)
	{
		r->dist_to_side[X] = (r->pos[X] - floor(r->pos[X])) * r->delta[X];
		r->step[X] = -1;
	}
	else
	{
		r->dist_to_side[X] = (floor(r->pos[X]) + 1.0 - r->pos[X]) * r->delta[X];
		r->step[X] = 1;
	}
	if (r->ray_dir[Y] < 0)
	{
		r->dist_to_side[Y] = (r->pos[Y] - floor(r->pos[Y])) * r->delta[Y];
		r->step[Y] = -1;
	}
	else
	{
		r->dist_to_side[Y] = (floor(r->pos[Y]) + 1.0 - r->pos[Y]) * r->delta[Y];
		r->step[Y] = 1;
	}
}

void	calc_dda(t_ray *r, t_view *v, char **map)
{
	r->wall_pos[X] = floor(r->pos[X]);
	r->wall_pos[Y] = floor(r->pos[Y]);
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
		if (map[(int)r->wall_pos[X]][(int)r->wall_pos[Y]] == C_WALL)
			break ;
	}
}

void	calc_perpendicular(t_ray *ray)
{
	if (ray->hit_side == false)
	{
		ray->wall_dist[X] = ray->wall_pos[X] - ray->pos[X] + (1 - ray->step[X]) / 2;
		ray->perp = fabs(ray->wall_dist[X] / ray->ray_dir[X]);
	}
	else
	{
		ray->wall_dist[Y] = ray->wall_pos[Y] - ray->pos[Y] + (1 - ray->step[Y]) / 2;
		ray->perp = fabs(ray->wall_dist[Y] / ray->ray_dir[Y]);
	}
	ray->line_size[0] = HEIGHT / 2 - (HEIGHT / ray->perp) / 2;
	ray->line_size[1] = HEIGHT / 2 + (HEIGHT / ray->perp) / 2;
}
