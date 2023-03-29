/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:22:49 by rlins             #+#    #+#             */
/*   Updated: 2023/03/28 20:16:15 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	args_handler(t_data *data, char **argv);

/**
 * @brief Will validate the inputs of program.
 * Then, will populate structures by params / handler arguments
 * @param data Data structure
 * @param argv Argument vector
 * @return int value of validations
 */
static int	args_handler(t_data *data, char **argv)
{
	if (val_cub_file(argv[1]) == false)
		return (error_msg(ERR_CUB, 4));
	init_map_handler(data, argv[1]);
	if (file_to_variable(data) != 0)
		return (free_data(data));
	if (valid_map(data) != 0)
		return (free_data(data));
	if (valid_texture(data, &data->texture_det) != 0)
		return (free_data(data));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error_msg(ERR_ARGS, 1));
	init_data(&data);
	if (args_handler(&data, argv) != 0)
		return (EXIT_FAILURE);
	ft_mlx_init(&data);
	mlx_loop(data.view.mlx);
	return (EXIT_SUCCESS);
}
