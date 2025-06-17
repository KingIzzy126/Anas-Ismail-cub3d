/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismailalashqar <ismailalashqar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:00:59 by ismailalash       #+#    #+#             */
/*   Updated: 2025/06/17 16:16:30 by ismailalash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_game(t_game *game, t_info *info)
{
    game->info = info;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Halo Infinite");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian); 
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    load_textures(game);
	init_player(&game->player, info);
    game->player.game = game;
}

void load_wall_textures(t_game *game)
{
	int i;
    char *paths[4] = {
        game->info->west_path,
        game->info->east_path,
        game->info->north_path,
        game->info->south_path 
	};
    
	i = 0;
    while (i < 4)
    {
        game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
            paths[i], &game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
		{
			fprintf(stderr, "Error: Failed to load wall texture from path: %s\n", paths[i]);
			exit(EXIT_FAILURE);  // Or handle gracefully if needed
		}
        game->textures[i].data = mlx_get_data_addr(game->textures[i].img,
            &game->textures[i].bpp, &game->textures[i].size_line, &game->textures[i].endian);
        i++;
    }
}

void load_visor_textures(t_game *game)
{
	int i;
    char *visor_paths[7] = { NULL,
        "visors/visor.xpm", "visors/visor2.xpm", "visors/visor3.xpm",
        "visors/visor4.xpm", "visors/visor5.xpm", "visors/visor6.xpm"
    };
	
	i = 1;
    while (i < 7)
    {
        game->visors[i].img = mlx_xpm_file_to_image(game->mlx, visor_paths[i],
            &game->visors[i].width, &game->visors[i].height);
        game->visors[i].data = mlx_get_data_addr(game->visors[i].img,
            &game->visors[i].bpp, &game->visors[i].size_line, &game->visors[i].endian);
        i++;
    }
    game->current_visor = 2; // start with visor2
}

void load_textures(t_game *game)
{
    load_wall_textures(game);
    load_visor_textures(game);
}
