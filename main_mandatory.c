/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:22:48 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/07/04 12:48:40 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **arg)
{
	t_info	info;
	t_game	game;
	int		fd;

	// Step 1: Init and parse map
	init_info(&info);    
	if (ac != 2)
		exitmassege("You Must Have One Map (chose_name.ber)\n", &info);
	fd = open_map_fd(arg[1], &info);
	map_pars_main(fd, &info);
	if (info.is_hv_err == 1)
	{
		if (info.fd > 0)
			close(info.fd);
		free_info(&info);
		return (1);
	}
	init_game(&game, &info);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	// free_info(&info);
	return (0);
}

