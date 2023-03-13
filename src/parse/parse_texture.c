/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:36:11 by rlins             #+#    #+#             */
/*   Updated: 2023/03/13 11:03:03 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	*parse_rgb_color(char *row);
static int	*parse_arr_color(char **str_rgb, int *rgb);
static bool	is_digit(char *str);

bool	parse_tex_color(t_texture_det *text_det, char *row, int i)
{
	if (row[i + 1] != C_WHITE_S)
	{
		error_msg(ERR_RGB, 10);
		return (false);
	}
	if (row[i] == 'C' && text_det->ceiling == NULL)
	{
		text_det->ceiling = parse_rgb_color(row + i + 1);
		if (text_det->ceiling == 0)
			error_msg(ERR_RGB, 10);
	}
	else if (row[i] == 'F' && text_det->floor == NULL)
	{
		text_det->floor = parse_rgb_color(row + i + 1);
		if (text_det->floor == 0)
			error_msg(ERR_RGB, 10);
	}
	else
	{
		error_msg(ERR_RGB, 10);
		return (false);
	}
	return (true);
}

/**
 * @brief Will handle the lines of ceiling and floor. Will receive the line
 * with this information, and will set the structure variables corresponding to
 * this value.
 * @param row Row to be handle in file
 * @return int* pointer to int with the information about the RGB color
 */
static int	*parse_rgb_color(char *row)
{
	char	**str_rgb;
	int		i;
	int		*rgb;

	i = 0;
	str_rgb = ft_split(row, ',');
	while (str_rgb[i])
		i++;
	if (i != 3)
	{
		free_array_str(str_rgb);
		return (0);
	}
	rgb = ft_calloc(3, sizeof(int));
	if (!rgb)
	{
		error_msg(ERR_MALC, 0);
		return (0);
	}
	return (parse_arr_color(str_rgb, rgb));
}

/**
 * @brief Will parse the array string (with 3 number, represented to RGB color)
 * to a integer array
 * @param str_rgb array of rgb color
 * @param rgb rgb pointer integer parsed
 */
static int	*parse_arr_color(char **str_rgb, int *rgb)
{
	int	i;

	i = 0;
	while (str_rgb[i])
	{
		rgb[i] = ft_atoi(str_rgb[i]);
		if (is_digit(str_rgb[i]) == false)
		{
			free_array_str(str_rgb);
			free_ptr(rgb);
			return(0);
		}
		i++;
	}
	free_array_str(str_rgb);
	return (rgb);
}

/**
 * @brief Verify each char if all is a valid digit.
 * @param str string to be verified
 * @return boolean - Is Valid or not
 */
static bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != C_WHITE_S && str[i] != '\n')
			if (ft_isdigit(str[i]) == false)
				return (false);
		i++;
	}
	return (true);
}


