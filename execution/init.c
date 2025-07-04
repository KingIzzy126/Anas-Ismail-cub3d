/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialashqa <ialashqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:00:59 by ismailalash       #+#    #+#             */
/*   Updated: 2025/07/02 11:36:29 by ialashqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game(t_game *game, t_info *info)
{
	game->info = info;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Halo Infinite");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	load_textures(game);
	game->shooting_frame = 0;
	init_player(&game->player, info);
	game->player.game = game;
}

void	load_wall_textures(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = game->info->west_path;
	paths[1] = game->info->east_path;
	paths[2] = game->info->north_path;
	paths[3] = game->info->south_path;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				paths[i], &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[3].img)
		{
			fprintf(stderr, "E: Failed to load texture path:%s\n", paths[i]);
			exit(EXIT_FAILURE);
		}
		game->textures[i].data = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].size_line,
				&game->textures[i].endian);
		i++;
	}
}

void	load_visor_textures(t_game *game)
{
	int		i;
	char	*v_path[6];

	v_path[0] = NULL;
	v_path[1] = "textures/visors/visor.xpm";
	v_path[2] = "textures/visors/visor2.xpm";
	v_path[3] = "textures/visors/visor3.xpm";
	v_path[4] = "textures/visors/visor4.xpm";
	v_path[5] = "textures/visors/visor5.xpm";
	i = 1;
	while (i <= 5)
	{
		game->visors[i].img = mlx_xpm_file_to_image(game->mlx, v_path[i],
				&game->visors[i].width, &game->visors[i].height);
		if (!game->visors[i].img)
		{
			fprintf(stderr, "E:Failed to load texture path:%s\n", v_path[i]);
			exit(EXIT_FAILURE);
		}
		game->visors[i].data = mlx_get_data_addr(game->visors[i].img,
				&game->visors[i].bpp, &game->visors[i].size_line,
				&game->visors[i].endian);
		i++;
	}
	game->current_visor = 2;
}

void	load_gun_textures(t_game *game)
{
	game->gun_normal.img = mlx_xpm_file_to_image(game->mlx,
			"textures/weapons/rifle.xpm", &game->gun_normal.width,
			&game->gun_normal.height);
	if (!game->gun_normal.img)
	{
		printf("E: Failed to load texture: rifle.xpm\n");
		exit(EXIT_FAILURE);
	}
	game->gun_normal.data = mlx_get_data_addr(game->gun_normal.img,
			&game->gun_normal.bpp, &game->gun_normal.size_line,
			&game->gun_normal.endian);
	game->gun_shoot.img = mlx_xpm_file_to_image(game->mlx,
			"textures/weapons/rifle_shooting.xpm",
			&game->gun_shoot.width, &game->gun_shoot.height);
	if (!game->gun_shoot.img)
	{
		printf("E: Failed to load texture: rifle_shooting.xpm\n");
		exit(EXIT_FAILURE);
	}
	game->gun_shoot.data = mlx_get_data_addr(game->gun_shoot.img,
			&game->gun_shoot.bpp, &game->gun_shoot.size_line,
			&game->gun_shoot.endian);
}

void	load_textures(t_game *game)
{
	load_wall_textures(game);
	load_visor_textures(game);
	load_gun_textures(game);
}
