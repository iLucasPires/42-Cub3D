/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:54:08 by rlins             #+#    #+#             */
/*   Updated: 2023/03/28 16:56:23 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static bool	is_map_sur_walls(t_data *data);
static int	is_valid_char_in_map(t_data *data, char **map);
static bool	is_map_last_element(t_map_det *map_det);

int	valid_map(t_data *data)
{
	int	valid_char_map;

	data->ray.dir_char = '0';
	if (!data->map)
		return (error_msg(ERR_MAP7, 7));
	if (is_map_sur_walls(data) == false)
		return (error_msg(ERR_MAP8, 8));
	valid_char_map = is_valid_char_in_map(data, data->map);
	if (valid_char_map != 0)
		return (valid_char_map);
	if (is_map_last_element(&data->map_det) == false)
		return (error_msg(ERR_MAP_LAST, 16));
	if (data->ray.dir_char == '0')
		return (error_msg(ERR_MAP_DIR, 17));

	return (0);
}

/**
 * @brief Map must be the last element in file. Verify if it is
 * @param map_det Map Detail Structure
 * @return boolean
 */
static bool	is_map_last_element(t_map_det *map_det)
{
	int	i;
	int	j;

	i = map_det->end_i_map;
	while (map_det->file[i])
	{
		j = 0;
		while (map_det->file[i][j])
		{
			if (map_det->file[i][j] != ' ' && map_det->file[i][j] != '\t' &&
				map_det->file[i][j] != '\n' && map_det->file[i][j] != '\r')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * @brief Handle the character in map. 6 possible characters: 0 for an empty
 * space, 1 for a wall, and N,S,E or W for the player’s start position
 * @param data Data structure
 * @param map Matrix representing map
 * @return int 0 OK. other wise: error
 */
static int	is_valid_char_in_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (is_white_space(map[i][j]))
				j++;
			if ((ft_strchr(VALID_CHAR_MAP, map[i][j])) == NULL)
				return (error_msg(ERR_MAP_CHAR, 10));
			if ((ft_strchr(VALID_PLAYER_POS, map[i][j])) != NULL)
			{
				if (data->ray.dir_char != C_BACK_G)
					return (error_msg(ERR_SING_PLAYER, 11));
				else
				{
					data->ray.pos[X] = i;
					data->ray.pos[Y] = j;
					data->ray.dir_char = map[i][j];
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Validate the Walls surrounded in map.
 * First look to first line.
 * Then, look in the last (bottom) line
 * Then, verify the first and the last column in each line
 * @param data
 * @return true
 * @return false
 */
static bool	is_map_sur_walls(t_data *data)
{
	int	i;
	int	j;
	int	col_size;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		col_size = ft_strlen(data->map[i]);
		while (data->map[i][j])
		{
			if (i == 0 && data->map[i][j] != C_WALL)
				return (false);
			else if (i == data->map_det.height -1 && data->map[i][j] != C_WALL)
				return (false);
			else if (j == 0 && data->map[i][j] != C_WALL)
				return (false);
			else if (j == (col_size - 1) && data->map[i][j] != C_WALL)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
