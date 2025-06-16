/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismailalashqar <ismailalashqar@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:00:59 by ismailalash       #+#    #+#             */
/*   Updated: 2025/06/16 19:48:05 by ismailalash      ###   ########.fr       */
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

void load_textures(t_game *game)
{
    char *paths[4] = {
        game->info->west_path,
        game->info->east_path,
        game->info->north_path,
        game->info->south_path
    };

    int i = 0;
    while (i < 4)
    {
        game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
            paths[i], &game->textures[i].width, &game->textures[i].height);
        game->textures[i].data = mlx_get_data_addr(game->textures[i].img,
            &game->textures[i].bpp, &game->textures[i].size_line, &game->textures[i].endian);
        i++;
    }
}

